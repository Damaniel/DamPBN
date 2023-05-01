#include "install.h"
#include "input.h"

int path_valid(char *path) {
    return 1;
}

void process_main_screen_input(unsigned char ascii_code, unsigned char scan_code, unsigned char shift_status) {
    switch (scan_code) {
        case KEY_ESC:
            g_exit = 1;
            break;
        case KEY_ENTER:
            if (path_valid(g_install_path)) {
                set_state(STATE_COPY_SCREEN);
            } 
            // Otherwise, shange to an error state
            else {
                set_state(STATE_INVALID_PATH_SCREEN);
            }
        default:
            break;
    }
}

void process_invalid_path_screen_input(unsigned char ascii_code, unsigned char scan_code, unsigned char shift_status) {
    switch (scan_code) {
        case KEY_ENTER:
            set_state(STATE_MAIN_SCREEN);
            break;
    }
}

void process_input(void) {
    unsigned short key, shift_status;
    unsigned char ascii_code, scan_code;

    // Get the shift state since it's non-blocking
    shift_status = _bios_keybrd(_KEYBRD_SHIFTSTATUS);
    // Is there a key ready?
    if (_bios_keybrd(_KEYBRD_READY)) {
        key = _bios_keybrd(_KEYBRD_READ);
        ascii_code = (key & 0xFF);
        scan_code = (key >> 8);
        switch(g_cur_state) {
            case STATE_MAIN_SCREEN:
                process_main_screen_input(ascii_code, scan_code, shift_status);
                break;
            case STATE_INVALID_PATH_SCREEN:
                process_invalid_path_screen_input(ascii_code, scan_code, shift_status);
                break;
            case STATE_COPY_SCREEN:
                break;
            case STATE_COMPLETE_SCREEN:
                break;
            default:
                break;
        }
    }
}
