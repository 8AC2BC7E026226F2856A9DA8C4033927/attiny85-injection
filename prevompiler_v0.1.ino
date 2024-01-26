#include "DigiKeyboard.h"
#include "avr/pgmspace.h"
#include "code_blocks.h"

#define PIN_LED 1 // led on model a
#define DEFAULT_LED_TIME 500

const char* printCharacter(const char* address, char character) {
  DigiKeyboard.print(character);
  return address;
}

void executeCodeBlock() {
  char currentCharacter;
  const char *currentAddress;

  for (int i = 0; i < NUM_INSTRUCTIONS; i++) {
    digitalWrite(PIN_LED, i % 2);
    
    // read initial character as identifier
    currentAddress = (char*)pgm_read_ptr(&(line_table[i]));
    currentCharacter = pgm_read_byte_near(currentAddress);  // strcpy_P performed horribly
    if (currentCharacter == '|') {
      // keypress instruction identifier
      pressSpecialKey(currentAddress);
      // DigiKeyboard.println("keypress");
    } else if (currentCharacter == '}') {
      // function key instruction identifier, add delay after keypress
      pressSpecialKey(currentAddress, true);
      // DigiKeyboard.print("function key");
    } else if (false) {
      // alt code instruction identifier
      DigiKeyboard.update();

      for (byte k = 1; k < 4; k++) {
        currentCharacter = pgm_read_byte_near(currentAddress + k);
        if (currentCharacter != '0') {
          DigiKeyboard.sendKeyPress((currentCharacter | 0xF000), MOD_ALT_LEFT);
        }
      }
    } else {
      // no identifier, handle as regular instruction
      int instructionLength = strlen_P(currentAddress);
      currentAddress = printCharacter(currentAddress, currentCharacter);
      for (byte k = 1; k < instructionLength; k++) {
        currentCharacter = pgm_read_byte_near(currentAddress + k);
        currentAddress = printCharacter(currentAddress, currentCharacter);
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