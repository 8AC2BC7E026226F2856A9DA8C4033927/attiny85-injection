import keyboard

global key_code
key_code = 0

def on_key_event(e):
    print(f'Key {e.name} {"" if e.event_type == keyboard.KEY_DOWN else "released"}')
    
    file = open('pressed.txt', 'a')
    file.write(f'{key_code}:\tKey {e.name} {"pressed" if e.event_type == keyboard.KEY_DOWN else "released"}\n')
    file.close()
    

try:
    keyboard.hook(on_key_event)
    keyboard.wait("ctrl+alt+esc")  # Wait for Ctrl+Alt+Esc to exit the loop
except KeyboardInterrupt:
    pass
finally:
    keyboard.unhook_all()