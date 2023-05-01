#include "install.h"
#include "textdraw.h"

State g_cur_state;
State g_prev_state;

int g_exit;

char g_install_path[MAX_PATH_LENGTH];
int g_edit_cursor_x, g_edit_cursor_y;

void set_state(State s) {
    g_prev_state = g_cur_state;
    g_cur_state = s;

    switch (g_cur_state) {
        case STATE_MAIN_SCREEN:
            strncpy(g_install_path, DEFAULT_PATH, MAX_PATH_LENGTH);
            g_edit_cursor_x = 34 + strlen(g_install_path);
            g_edit_cursor_y = 18;
            g_render_components.background = 1;
            g_render_components.intro_window = 1;
            g_render_components.destination_edit_area = 1;
            g_render_components.destination_edit = 1;
            g_render_components.top_status_text = 1;
            g_render_components.bottom_status_text = 1;
            break;
        case STATE_INVALID_PATH_SCREEN:
            g_render_components.background = 1;
            g_render_components.intro_window = 1;
            g_render_components.destination_edit_area = 1;
            g_render_components.destination_edit = 1;
            g_render_components.top_status_text = 1;
            g_render_components.bottom_status_text = 1;
            g_render_components.error_message = 1;
            break;
        default:
            break;
    };
}

int main(void) {
    int result;
    char *path = "C:\\DAMPBN\\";
    g_exit = 0;

    printf("Path is %s\n", path);
    result = is_path_valid(path, 1, 3);
    switch (result) {
        case 0:
            printf("Error while checking path!\n");
            break;
        case 1:
            printf("Path is valid and doesn't exist yet!\n");
            break;
        case 2:
            printf("Path is valid but exists already!\n");
            break;
    }

    return 0;

    // g_cur_state = STATE_MAIN_SCREEN;
    // g_prev_state = STATE_MAIN_SCREEN;

    // set_text_mode(MODE_80X25);
    // set_bg_intensity(1);
    // clear_screen();
    // init_render_colors();

    // set_state(STATE_MAIN_SCREEN);
    
    // while (!g_exit) {
    //     process_input();
    //     render();
    // }

    // clear_screen();

    // return 0;
}
