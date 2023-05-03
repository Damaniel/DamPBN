#include "install.h"
#include "render.h"

RenderComponents g_render_components;
RenderColors g_render_colors;

void init_render_colors(void) {
    g_render_colors.background = make_attr(COLOR_LIGHT_BLUE, COLOR_BLUE);
    g_render_colors.status_bar = make_attr(COLOR_WHITE, COLOR_LIGHT_CYAN);
    g_render_colors.status_text = make_attr(COLOR_BLACK, COLOR_LIGHT_CYAN);
    g_render_colors.box_edge = make_attr(COLOR_WHITE, COLOR_CYAN);
    g_render_colors.box_text = make_attr(COLOR_YELLOW, COLOR_CYAN);
    g_render_colors.edit_box = make_attr(COLOR_WHITE, COLOR_BLUE);
    g_render_colors.edit_text = make_attr(COLOR_BLUE, COLOR_WHITE);
    g_render_colors.error_box = make_attr(COLOR_YELLOW, COLOR_RED);
    g_render_colors.error_text = make_attr(COLOR_WHITE, COLOR_RED);
}

void clear_render_components(void) {
    g_render_components.intro_window = 0;
    g_render_components.background = 0;
    g_render_components.destination_edit = 0;
    g_render_components.top_status_text = 0;
    g_render_components.bottom_status_text = 0;
    g_render_components.error_message = 0;
}

void render_invalid_path_screen(void) {
    if (g_render_components.error_message) {
        box_at(10, 12, 69, 17, BORDER_SINGLE, g_render_colors.error_box);
        fill_box_at(11, 13, 68, 16, ' ', g_render_colors.error_text);
        string_at(12, 13, "   The specified path is invalid or there isn't enough", g_render_colors.error_text);
        string_at(12, 14, "           disk space to complete the install.", g_render_colors.error_text);
        string_at(12, 16, "                Press ENTER to try again.", g_render_colors.error_text);
        g_render_components.error_message = 0;
    }
}

void render_confirm_existing_screen(void) {
    if (g_render_components.confirm_existing_message) {
        box_at(10, 12, 69, 17, BORDER_SINGLE, g_render_colors.error_box);
        fill_box_at(11, 13, 68, 16, ' ', g_render_colors.error_text);
        string_at(12, 13, "    The specified path already exists.  Are you sure", g_render_colors.error_text);
        string_at(12, 14, "               you want to install here?            ", g_render_colors.error_text);
        string_at(12, 16, "                     Press Y or N.                  ", g_render_colors.error_text);    
        g_render_components.confirm_existing_message = 0;   
    }
}

void render_progress_screen(void) {
    char buf[80];
    float progress_pct;
    int bar_length, step;

    render_main_screen();

    if (g_render_components.progress_message_window) {
        box_at(8, 3, 71, 15, BORDER_DOUBLE, g_render_colors.box_edge);
        fill_box_at(9, 4, 70, 14, ' ', g_render_colors.box_text);
        string_at(10, 5, "   The game files are now being copied to the hard drive.", g_render_colors.box_text);
        string_at(10, 8, "Read the README.md file for more information about the game", g_render_colors.box_text);
        string_at(10, 9, "   and for information about tools you can use to create", g_render_colors.box_text);
        string_at(10, 10, "                     your own images. ", g_render_colors.box_text);
        string_at(10, 13, "        This shouldn't take too long, I promise...", g_render_colors.box_text);
        g_render_components.progress_message_window = 0;
    }

    if (g_render_components.progress_box) {
        box_at(4, 18, 75, 21, BORDER_DOUBLE, g_render_colors.box_edge);
        fill_box_at(5, 19, 74, 20, ' ', g_render_colors.box_text);
        g_render_components.progress_box = 0;
    }

    if (g_render_components.progress_bar) {
        step = g_manifest.cur_step_idx - 1;
        progress_pct = (float)step / (float)g_manifest.num_steps;
        bar_length = (int)(floor(67.0 * progress_pct));
        fill_box_at(6, 20, 73, 20, ' ', g_render_colors.edit_box);
        fill_box_at(6, 20, 6 + bar_length - 1, 20, 219, g_render_colors.edit_box);
        g_render_components.progress_bar = 0;
    }

    if (g_render_components.progress_name) {
        string_at(6, 19, "                                                                    ", g_render_colors.box_text);
        switch(g_manifest.ms.operation) {
            case MKDIR:
                snprintf(buf, 70, "Creating directory %s...", g_manifest.ms.source);
                string_at(6, 19, buf, g_render_colors.box_text);
                break;
            case COPY:
                snprintf(buf, 70, "Copying %s...", g_manifest.ms.source, g_manifest.ms.dest);
                string_at(6, 19, buf, g_render_colors.box_text);
                break;
            case COPYDIR:
                snprintf(buf, 70, "Copying directory %s...", g_manifest.ms.source, g_manifest.ms.dest);
                string_at(6, 19, buf, g_render_colors.box_text);
                break;
        }
        g_render_components.progress_name = 0;
    }
}

void render_main_screen(void) {
    char debug_text[80];

    if (g_render_components.background) {
        fill_box_at(0, 0, 79, 24, 177, g_render_colors.background);
        hline_at(0, 0, 80, ' ', g_render_colors.status_bar);
        hline_at(0, 24, 80, ' ', g_render_colors.status_bar);
        g_render_components.background = 0;
    }
    if (g_render_components.top_status_text) {
        string_at(29, 0, "DamPBN Installer v1.00", g_render_colors.status_text);
        g_render_components.top_status_text = 0;
    }
    if (g_render_components.bottom_status_text) {
        string_at(26, 24, "Copyright 2023 Shaun Brandt", g_render_colors.status_text);
        g_render_components.bottom_status_text = 0;
    }
    if (g_render_components.intro_window) {
        box_at(8, 3, 71, 15, BORDER_DOUBLE, g_render_colors.box_edge);
        fill_box_at(9, 4, 70, 14, ' ', g_render_colors.box_text);
        string_at(10, 5, "             Thank you for installing DamPBN!", g_render_colors.box_text);
        string_at(10, 7, "  This installer will copy the game and image files to the", g_render_colors.box_text);
        string_at(10, 8, "    directory specified below.  If you want to change the", g_render_colors.box_text);
        string_at(10, 9, "default path, type the name of the new path.  Once complete,", g_render_colors.box_text);
        string_at(10, 10, "         press ENTER to install, or ESC to exit. ", g_render_colors.box_text);
        string_at(10, 13, "  NOTE: the installation will use about 1MB of disk space.", g_render_colors.box_text);
        g_render_components.intro_window = 0;
    }
    if (g_render_components.destination_edit_area) {
        box_at(20, 17, 59, 19, BORDER_SINGLE, g_render_colors.box_edge);
        string_at(21, 18, " Install to: ", g_render_colors.box_text);
        string_at(PATH_EDIT_BOX_X, 18, "                        ", g_render_colors.edit_box);
        string_at(58, 18, " ", g_render_colors.box_text);
        g_render_components.destination_edit_area = 0;
    }

    if (g_render_components.destination_edit) {
        char a;
        render_path_text(g_edit_display_offset);
        a = get_letter_under_cursor(g_edit_cursor_x, g_edit_display_offset);
        char_at(g_edit_cursor_x, g_edit_cursor_y, a, g_render_colors.edit_text);
        g_render_components.destination_edit = 0;
        if (g_old_edit_cursor_x + g_edit_display_offset - PATH_EDIT_BOX_X  == strlen(g_install_path) && g_edit_cursor_x + g_edit_display_offset - PATH_EDIT_BOX_X == strlen(g_install_path) - 1) {
            char_at(g_old_edit_cursor_x, g_edit_cursor_y, ' ' , g_render_colors.edit_box);
        } 
        if (g_old_edit_cursor_x == PATH_EDIT_BOX_X + MAX_VISIBLE_PATH_LENGTH - 1 && g_edit_cursor_x == PATH_EDIT_BOX_X + MAX_VISIBLE_PATH_LENGTH - 2) {
            char_at(PATH_EDIT_BOX_X + MAX_VISIBLE_PATH_LENGTH - 1, g_edit_cursor_y, ' ', g_render_colors.edit_box);
        }
    }

    if (g_render_components.debug_text) {
        memset(debug_text, '\0', 80);
        snprintf(debug_text, 79, " Cursor X: %d, under cursor = %c ", g_edit_cursor_x, (g_edit_cursor_x + g_edit_display_offset - PATH_EDIT_BOX_X >= strlen(g_install_path)) ? ' ' : g_install_path[g_edit_cursor_x + g_edit_display_offset - PATH_EDIT_BOX_X]);
        string_at(5, 20, debug_text, g_render_colors.box_text);
        memset(debug_text, '\0', 80);
        snprintf(debug_text, 79, " Edit display offset: %d ", g_edit_display_offset);
        string_at(5, 21, debug_text, g_render_colors.box_text);
        memset(debug_text, '\0', 80);
        snprintf(debug_text, 79, " Path: %s ", g_install_path);
        string_at(5, 22, debug_text, g_render_colors.box_text);
        memset(debug_text, '\0', 80);
        snprintf(debug_text, 79, " Offset in string: %d, strlen = %d ", g_edit_cursor_x + g_edit_display_offset - PATH_EDIT_BOX_X, strlen(g_install_path));
        string_at(5, 23, debug_text, g_render_colors.box_text);
        g_render_components.debug_text = 0;
    }
}

void render_copy_error_screen(void) {
    // The error message is built on top of the progress screen
    render_progress_screen();
    if (g_render_components.copy_error_message) {
        box_at(10, 11, 69, 16, BORDER_SINGLE, g_render_colors.error_box);
        fill_box_at(11, 12, 68, 15, ' ', g_render_colors.error_text);
        string_at(12, 12, "     An error occurred while copying files to disk.", g_render_colors.error_text);
        string_at(12, 13, "             The installer will now exit.", g_render_colors.error_text);
        string_at(12, 15, "                     Press ENTER.", g_render_colors.error_text);    
        g_render_components.copy_error_message = 0;   
    }
}

void render_complete_screen(void) {
    // results are stacked on top of the main screen, so draw it first
    render_main_screen();
    if (g_render_components.complete_message) {
        box_at(10, 9, 69, 14, BORDER_SINGLE, g_render_colors.box_edge);
        fill_box_at(11, 10, 68, 13, ' ', g_render_colors.box_text);
        string_at(12, 10, "              Installation is now complete.", g_render_colors.box_text);
        string_at(12, 11, "          Thanks for installing DamPBN. Enjoy!", g_render_colors.box_text);
        string_at(12, 13, "                 Press ENTER to exit.", g_render_colors.box_text);
        g_render_components.complete_message = 0;   
    }
}

char get_letter_under_cursor(int cursor_pos, int left_offset) {
    int offset = left_offset + cursor_pos - PATH_EDIT_BOX_X ;
    // If there is a letter under the cursor, then return it
    if (offset < strlen(g_install_path)) {
        return g_install_path[offset];
    }
    return ' ';
}

void set_letter_under_cursor(int cursor_pos, int left_offset, char c) {
    int offset = left_offset + cursor_pos - PATH_EDIT_BOX_X;
    if (offset < strlen(g_install_path)) {
        g_install_path[offset] = c;        
    }
}

void render_path_text(int left_offset) {
    int len, empty_space_in_box, i;
    char path[MAX_VISIBLE_PATH_LENGTH + 1];

    len = strlen(g_install_path);
    if ((len - left_offset) > MAX_VISIBLE_PATH_LENGTH) {
        strncpy(path, g_install_path+left_offset, MAX_VISIBLE_PATH_LENGTH);
    } else {
        strncpy(path, g_install_path+left_offset, MAX_VISIBLE_PATH_LENGTH);
    }
    path[MAX_VISIBLE_PATH_LENGTH] = '\0';
    string_at(PATH_EDIT_BOX_X, 18, path, g_render_colors.edit_box);
    // Figure out how much empty space is in the box after the remaining string,
    // and clear it out
    empty_space_in_box = MAX_VISIBLE_PATH_LENGTH - len - left_offset;
    for(i=0;i<empty_space_in_box;i++) {
        char_at(PATH_EDIT_BOX_X + MAX_VISIBLE_PATH_LENGTH - i - 1, 18, ' ', g_render_colors.edit_box);
    }
}

void render(void) {
    switch (g_cur_state) {
        case STATE_MAIN_SCREEN:
            render_main_screen();
            break;
        case STATE_INVALID_PATH_SCREEN:
            render_invalid_path_screen();
            break;
        case STATE_CONFIRM_EXISTING_SCREEN:
            render_confirm_existing_screen();
            break;
        case STATE_COPY_SCREEN:
            render_progress_screen();
            // Sleep for a bit to progress the bar
            break;
        case STATE_COMPLETE_SCREEN:
            render_complete_screen();
            break;
        case STATE_COPY_ERROR_SCREEN:
            render_copy_error_screen();
            break;
        default:
            break;
    };
}

