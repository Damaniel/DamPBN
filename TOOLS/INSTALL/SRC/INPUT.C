#include "install.h"
#include "input.h"

void process_main_screen_input(unsigned char ascii_code, unsigned char scan_code, unsigned char shift_status) {
    int cursor_position_in_string = g_edit_cursor_x + g_edit_display_offset - PATH_EDIT_BOX_X;
    int cursor_position_in_box = g_edit_cursor_x - PATH_EDIT_BOX_X;
    int string_length = strlen(g_install_path);
    int i, moved;

    switch (scan_code) {
        case KEY_ESC:
            g_exit = 1;
            break;
        case KEY_ENTER:
            switch(is_path_valid(g_install_path, 1, REQUIRED_MB)) {
                case 0:
                    set_state(STATE_INVALID_PATH_SCREEN);
                    break;
                case 1:
                    set_state(STATE_COPY_SCREEN);
                    break;
                case 2:
                    // pop up a dialog confirming they want to install to an existing directory
                    set_state(STATE_CONFIRM_EXISTING_SCREEN);
                    break;
            }
            break;
        case KEY_LEFT:
            // If the cursor is to the right of the leftmost position
            //   Move the cursor one to the left
            // If the cursor is already all the way to the left of the screen, but not the string
            //   Move the display offset one to the left
            if (cursor_position_in_box > 0) {
                g_old_edit_cursor_x = g_edit_cursor_x;
                g_edit_cursor_x = g_edit_cursor_x - 1;
            }
            else if(g_edit_display_offset > 0) {
                g_edit_display_offset = g_edit_display_offset - 1;
            }
            g_render_components.destination_edit = 1;
            break;
        case KEY_RIGHT:
            // If the cursor (cursor offset + display_offset) isn't already at the current length of the string
            //      If the cursor is to the left of the rightmost position
            //          Move the cursor one to the right
            //      If the cursor is all the way to the right of the screen
            //          Move the display offset one to the right
            if(cursor_position_in_box + g_edit_display_offset < strlen(g_install_path)) {
                if (cursor_position_in_box < MAX_VISIBLE_PATH_LENGTH - 1) {
                    g_old_edit_cursor_x = g_edit_cursor_x;
                    g_edit_cursor_x = g_edit_cursor_x + 1;
                } else if (cursor_position_in_string < strlen(g_install_path)) {
                    g_edit_display_offset = g_edit_display_offset + 1;
                }
                g_render_components.destination_edit = 1;
            }
            break;
        case KEY_DELETE:
            // Shift all characters to the right left by one
            // Set the last character to \0
            for (i=cursor_position_in_string; i< MAX_PATH_LENGTH; i++) {
                g_install_path[i] = g_install_path[i+1];    
            }
            g_install_path[MAX_PATH_LENGTH-1] = '\0';
            g_render_components.destination_edit = 1;
            break;
        case KEY_BACKSPACE:
            // If the cursor isn't to the right of the leftmost position
            //   Move the cursor one to the left
            //  If the cursor is already all the way to the left of the screen, but not the string
            //   Move the display offset one to the left
            //  Shift all characters to the left by one
            //  Set the last character to \0
            moved = 0;
            if (cursor_position_in_box > 0) {
                g_old_edit_cursor_x = g_edit_cursor_x;
                g_edit_cursor_x = g_edit_cursor_x - 1;
                moved = 1;
            }
            else if (g_edit_display_offset > 0) {
                g_edit_display_offset = g_edit_display_offset -1;
                moved = 1;
            }
            if (moved) {
                cursor_position_in_string = g_edit_cursor_x + g_edit_display_offset - PATH_EDIT_BOX_X;
                for (i=cursor_position_in_string; i < MAX_PATH_LENGTH; i++) {
                    g_install_path[i] = g_install_path[i+1];
                }
            }
            g_install_path[MAX_PATH_LENGTH-1] = '\0';
            g_render_components.destination_edit = 1;
            break;
        default:
            break;
    }
    if ((ascii_code >= 'a' && ascii_code <= 'z') ||
        (ascii_code >= 'A' && ascii_code <= 'Z') ||
        (ascii_code >= '0' && ascii_code <= '9') ||
        ascii_code == '.' || ascii_code == ':' || ascii_code == '\\' || ascii_code == '$' || ascii_code == '-' || ascii_code == '_') {
        // Type the new character at the current cursor position 
        // If the cursor (cursor offset + display) isn't already the maximum length of the string
        //      If the cursor is to the left of the rightmost position
        //          Move the cursor one to the right
        //      If the cursor is all the way to the right of the screen
        //          Move the display offset one to the right
        //
        g_install_path[cursor_position_in_string] = ascii_code;
        if (cursor_position_in_string < MAX_PATH_LENGTH - 1) {
            if (cursor_position_in_box < MAX_VISIBLE_PATH_LENGTH - 1) {
                g_old_edit_cursor_x = g_edit_cursor_x;
                g_edit_cursor_x = g_edit_cursor_x + 1;
            } else if (cursor_position_in_string < strlen(g_install_path)) {
                g_edit_display_offset = g_edit_display_offset + 1;
            }
        }
        g_render_components.destination_edit = 1;
    }
}

void process_invalid_path_screen_input(unsigned char ascii_code, unsigned char scan_code, unsigned char shift_status) {
    switch (scan_code) {
        case KEY_ENTER:
            set_state(STATE_MAIN_SCREEN);
            break;
    }
}

void process_confirm_existing_screen_input(unsigned char ascii_code, unsigned char scan_code, unsigned char shift_status) {
    switch (scan_code) {
        case KEY_Y:
            set_state(STATE_COPY_SCREEN);
            break;
        case KEY_N:
            set_state(STATE_MAIN_SCREEN);
            break;
        default:
            break;
    }
}

void process_copy_screen_input(unsigned char ascii_code, unsigned char scan_code, unsigned char shift_status) {
    switch (scan_code) {
        case KEY_ENTER:
        case KEY_ESC:
            g_exit = 1;
    }
}

void process_complete_screen_input(unsigned char ascii_code, unsigned char scan_code, unsigned char shift_status) {
    switch (scan_code) {
        case KEY_ENTER:
            g_exit = 1;
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
            case STATE_CONFIRM_EXISTING_SCREEN:
                process_confirm_existing_screen_input(ascii_code, scan_code, shift_status);
                break;
            case STATE_COPY_SCREEN:
                // Note: this is only for debug - the copy phase won't actually have input
                process_copy_screen_input(ascii_code, scan_code, shift_status);
                break;
            case STATE_COMPLETE_SCREEN:
                process_complete_screen_input(ascii_code, scan_code, shift_status);
                break;
            default:
                break;
        }
    }
}
