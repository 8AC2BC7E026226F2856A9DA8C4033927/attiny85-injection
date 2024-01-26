// slightly more storage efficient, but performs horribly
const char *currentAddress;
void executeCodeBlock() {
  for (int i = 0; i < NUM_LINES; i++) {
    // digitalWrite(PIN_LED, i % 2);

    currentAddress = (char*)pgm_read_ptr(&(line_table[i]));
    if (currentAddress == key_printGreaterThan) {
      printGreaterThan();
      DigiKeyboard.println("greater than");
    } else {
      strcpy_P(buffer, currentAddress);
      DigiKeyboard.println(buffer);
    }
    
    DigiKeyboard.delay(500);
  }
}

void openAdminShell() {
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(500);
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(500);
  DigiKeyboard.print("Powershell /Command ");
  DigiKeyboard.sendKeyStroke(KEY_2, MOD_SHIFT_LEFT);  // print double quote
  DigiKeyboard.print("Start/Process cmd /Verb RunAs");
  DigiKeyboard.sendKeyStroke(KEY_2, MOD_SHIFT_LEFT);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(3000);
  DigiKeyboard.sendKeyStroke(KEY_ARROW_LEFT);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(500);
  DigiKeyboard.println("echo sucess");
}

void setup() {
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);
  /*
  DigiKeyboard.print("&%^*@, )");
  DigiKeyboard.sendKeyStroke(0x64);
  DigiKeyboard.sendKeyStroke(0x36);
  DigiKeyboard.sendKeyStroke(0x36,MOD_ALT_LEFT);
  DigiKeyboard.update();
  DigiKeyboard.sendKeyPress(KEYPAD_6,MOD_ALT_LEFT);
  DigiKeyboard.sendKeyPress(KEYPAD_2,MOD_ALT_LEFT);
  DigiKeyboard.sendKeyPress(0,0);   
  DigiKeyboard.delay(100);

  for (int i = 0; i < 1000; i++) {
    DigiKeyboard.sendKeyStroke(i);
    DigiKeyboard.delay(200);
    DigiKeyboard.sendKeyStroke(i,MOD_ALT_LEFT);
    DigiKeyboard.delay(200);
  }
  */
  // test();
  
  // DigiKeyboard.print(lorem);
  /*
  int signMessageLength = strlen_P(lorem);
  for (byte k = 0; k < signMessageLength; k++) {
    myChar = pgm_read_byte_near(lorem + k);
    DigiKeyboard.print(myChar);
  }
  */
  executeCodeBlock();
  // openAdminShell();
  /*
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(500);
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(500);
  DigiKeyboard.sendKeyStroke(KEY_R);
  DigiKeyboard.print("Powershell /Command ");
  DigiKeyboard.delay(500);
  */
  digitalWrite(PIN_LED, LOW);
}