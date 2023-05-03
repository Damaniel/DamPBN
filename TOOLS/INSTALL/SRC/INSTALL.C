#include "install.h"
#include "textdraw.h"

State g_cur_state;
State g_prev_state;

int g_exit;

char g_install_path[MAX_PATH_LENGTH + 1];
int g_edit_cursor_x, g_edit_cursor_y, g_old_edit_cursor_x;
int g_edit_display_offset;

void set_state(State s) {
    g_prev_state = g_cur_state;
    g_cur_state = s;

    switch (g_cur_state) {
        case STATE_MAIN_SCREEN:
            if(g_prev_state == STATE_MAIN_SCREEN || g_prev_state == STATE_INVALID_PATH_SCREEN) {
                strncpy(g_install_path, DEFAULT_PATH, MAX_PATH_LENGTH);
                if(strlen(g_install_path) > MAX_VISIBLE_PATH_LENGTH) {
                    g_edit_cursor_x = 34 + MAX_VISIBLE_PATH_LENGTH;
                } else {
                    g_edit_cursor_x = 34 + strlen(g_install_path);
                }
            }
            g_old_edit_cursor_x = g_edit_cursor_x;
            g_edit_cursor_y = 18;
            g_edit_display_offset = 0;
            g_render_components.background = 1;
            g_render_components.intro_window = 1;
            g_render_components.destination_edit_area = 1;
            g_render_components.destination_edit = 1;
            g_render_components.top_status_text = 1;
            g_render_components.bottom_status_text = 1;
            g_render_components.debug_text = 0;
            break;
        case STATE_INVALID_PATH_SCREEN:
            g_render_components.error_message = 1;
            break;
        case STATE_CONFIRM_EXISTING_SCREEN:
            g_render_components.confirm_existing_message = 1;
            break;
        case STATE_COPY_SCREEN:
            g_install_path[MAX_PATH_LENGTH] = '\0';
            g_render_components.background = 1;
            g_render_components.top_status_text = 1;
            g_render_components.bottom_status_text = 1;
            g_render_components.progress_bar = 1;
            g_render_components.progress_box = 1;
            g_render_components.progress_message_window = 1;
            g_render_components.progress_name = 1;
            perform_copy_steps();
            set_state(STATE_COMPLETE_SCREEN);
            break;
        case STATE_COMPLETE_SCREEN:
            g_render_components.background = 1;
            g_render_components.top_status_text = 1;
            g_render_components.bottom_status_text = 1;
            g_render_components.complete_message = 1;   
            break;
        default:
            break;
    };
}

int perform_copy_steps(void) {
    int result;

    set_manifest_base_path(&g_manifest, g_install_path);

    while (!manifest_complete(&g_manifest)) {
        result = get_manifest_step(&g_manifest);
        if(result != 0) {
            return -1;
        }
        g_render_components.progress_bar = 1;
        g_render_components.progress_name = 1;
        // Force a render update
        render();
        //result = perform_manifest_step(&g_manifest);
        //if (result !=0) {
        //    return -1;           
        //}
    }

    return 0;
}

int main(void) {
    int result;
    g_exit = 0;

    result = load_manifest("MANIFEST", &g_manifest);
    if (result != 0) {
         printf("Couldn't load manifest!\n");
         return -1;
    }

    g_cur_state = STATE_MAIN_SCREEN;
    g_prev_state = STATE_NONE;

    set_text_mode(MODE_80X25);
    set_bg_intensity(1);
    clear_screen();
    init_render_colors();

    set_state(STATE_MAIN_SCREEN);
    
    while (!g_exit) {
        process_input();
        render();
    }

    clear_screen();

    unload_manifest(&g_manifest);

    return 0;
}
