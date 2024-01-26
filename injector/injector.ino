#include "DigiKeyboard.h"
#include "avr/pgmspace.h"
#include "code_blocks.h"

#define PIN_LED 1 // led on model a
#define DEFAULT_LED_TIME 500
#define DEFAULT_DELAY_TIME 400

void printCharacter(const char* address, byte& offset, char character) {
  if (character == '~') {
    // alt code identifier
    DigiKeyboard.update();

    // fetch alt code in following 3 bytes
    for (byte k = 1; k < 4; k++) {
      character = pgm_read_byte_near(address + offset + k);
      if (character != '0') {
        DigiKeyboard.sendKeyPress(character | 0xF000, MOD_ALT_LEFT);
      }
    }
    DigiKeyboard.sendKeyPress(0,0);

    // skip alt code in next fetch cycle
    offset += 3;
  } else if(character == '@') {
    // delay identifier
    DigiKeyboard.delay(DEFAULT_DELAY_TIME);
  } else {
    // no identifier, print regular character
    DigiKeyboard.print(character);
  }
}

void executeCodeBlock() {
  const char *address;
  byte offset = 0;
  char character;

  for (int i = 0; i < NUM_INSTRUCTIONS; i++) {
    digitalWrite(PIN_LED, i % 2);
    
    // read initial character as identifier
    address = (char*)pgm_read_ptr(&(line_table[i]));
    character = pgm_read_byte_near(address);  // strcpy_P performed horribly
    if (character == '|') {
      // keypress instruction identifier
      pressSpecialKey(address);
      
    } else if (character == '}') {
      // function key instruction identifier, add delay after keypress
      pressSpecialKey(address, true);
    } else {
      // no identifier, handle as regular instruction
      int instructionLength = strlen_P(address);
      for (byte offset = 0; offset < instructionLength; offset++) {
        character = pgm_read_byte_near(address + offset);
        printCharacter(address, offset, character);
      }
    }
  }
}

void setup() {
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);
  executeCodeBlock();
  digitalWrite(PIN_LED, LOW);

  // exit signal
  while(true) {
    digitalWrite(PIN_LED, HIGH);
    delay(DEFAULT_LED_TIME);
    digitalWrite(PIN_LED, LOW);
    delay(DEFAULT_LED_TIME);
  }
}

void loop() {}