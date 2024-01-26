import re
import sys
import pyperclip
from alt_codes import *

open_tmp_console = 'cmd /k cd %temp%'
run_without_elevation = 'cmd /min /C "set __COMPAT_LAYER=RUNASINVOKER && start "" regedit"'
enable_numlock = 'Powershell [CONSOLE]::NumberLock | FIND /I "FALSE">NUL&&' + "Powershell ($WSH = New-Object -ComObject WScript.Shell)-AND($WSH.SendKeys('{NUMLOCK}'))>NUL"
disable_numlock = 'Powershell [CONSOLE]::NumberLock | FIND /I "TRUE">NUL&&' + "Powershell ($WSH = New-Object -ComObject WScript.Shell)-AND($WSH.SendKeys('{NUMLOCK}'))>NUL"

class KeyCodes:
    keypad_f0_offset = {
        0: 98,
        1: 89,
        2: 90,
        3: 91,
        4: 92,
        5: 93,
        6: 94,
        7: 95,
        8: 96,
        9: 97,
    }

special_keys = {
    'key_enter': 'DigiKeyboard.sendKeyStroke(KEY_ENTER);',
    'key_arrow_left': 'DigiKeyboard.sendKeyStroke(KEY_ARROW_LEFT);',
    'key_double_quotes': 'DigiKeyboard.sendKeyStroke(KEY_2, MOD_SHIFT_LEFT);',
    'fn_run': '''DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
    DigiKeyboard.delay(500);''',
}

files = {
    'BackgroundLoader.vbs': 'CreateObject("Shell.Application").ShellExecute "script.bat",,"","runas",1',
    'Script.bat': 'set /p DUMMY=Hit ENTER to continue...'
}

if len (sys.argv) < 2:
    print('Error: No input file specified')
    exit()

with open(sys.argv[1], 'r') as code_file:
    commands = code_file.read()

def replace_special_characters(string: str):
    replacement_mappings = {}

    for character in string:
        if character in alt_codes.keys():
            alt_code = alt_codes[character]
            indiviual_keys = list(map(int, str(alt_code)))

            compiled_alt_code = '~'
            for key in indiviual_keys:
                compiled_alt_code += chr(KeyCodes.keypad_f0_offset[key])
            
            # pad 0 if neccessary
            if len(compiled_alt_code) < 4:
                compiled_alt_code += '0'
            
            replacement_mappings[character] = compiled_alt_code
    
    mapped = ''
    for character in string:
        if character in replacement_mappings:
            mapped += replacement_mappings[character]
        else:
            mapped += character
    
    return mapped.replace('\\', '\\\\')

end_directive = False
def filter_line(line: str):
    global end_directive
    if line and line[:4] == '@end':
        end_directive = True

    return not end_directive and line and line[:5] != '@rem '

code_lines = re.split(f'\n|({")|(".join(special_keys.keys())})', commands)
code_lines = list(filter(lambda line: filter_line(line), code_lines))    # filter out empty lines

special_keys_used = [key for key in special_keys.keys() if key in code_lines]
code_lines_runnable = [line for line in code_lines if not line in special_keys_used]
print('\nRaw Code Lines:')
print(code_lines)
print('\nSpecial Keys Used:')
print(special_keys_used)

print(f'{"-" * 20}\n\nCompressed Code:\n')
code_block = '#include "DigiKeyboard.h"\n\n'
code_block += '// declare special key addresses\n'

# add key addresses
for key in special_keys_used:
    if key[:3] == "key":
        identifier = '|'
    else:
        identifier = '}'
    
    code_block += f'const char {key}[] PROGMEM = "{identifier}";\n'
code_block += '\n// store instructions in flash memory and read sequentially to save sram\n'

line_table = '\n// instruction lookup table (execution order: left to right)'
line_table += '\nconst char *const line_table[] PROGMEM = { '
for line in code_lines:
    if line in special_keys_used:
        line_table += f', {line}'
    else:
        line_index = code_lines_runnable.index(line)
        line_table += f', line_{line_index}'

        if line[:8] != '@no_alt ':
            line = replace_special_characters(line)
        else:
            line = line.replace('@no_alt ', '', 1)
        code_block += f'const char line_{line_index}[] PROGMEM = "{line}";\n'

line_table = line_table.replace(', ','',1)
line_table += ' };'

code_block += line_table
code_block += f'\nconst int NUM_INSTRUCTIONS = {len(code_lines)};\n\n'

special_key_function = '// presses the key associated with the key code\n'
special_key_function += 'void pressSpecialKey(const char* address, bool fnDelay = false) {\n'
for key, function in special_keys.items():
    if key in special_keys_used:
        special_key_function += f' else if (address == {key}) {{\n    {function}\n  }}'
special_key_function = special_key_function.replace(' else ', '  ', 1)
code_block += special_key_function + ''' else {
    return; // no delay needed
  }\n
  if (fnDelay) {
    DigiKeyboard.delay(500);
  }
}'''

pyperclip.copy(code_block)
print(code_block)
print('\n-- Copied to clipboard --')