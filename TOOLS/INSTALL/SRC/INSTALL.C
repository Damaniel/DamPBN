#include "install.h"
#include "textdraw.h"

State g_cur_state;
State g_prev_state;

int g_exit;

char g_install_path[MAX_PATH_LENGTH];
int g_edit_cursor_x, g_edit_cursor_y, g_old_edit_cursor_x;
int g_edit_display_offset;

void set_state(State s) {
    g_prev_state = g_cur_state;
    g_cur_state = s;

    switch (g_cur_state) {
        case STATE_MAIN_SCREEN:
            strncpy(g_install_path, DEFAULT_PATH, MAX_PATH_LENGTH);
            if(strlen(g_install_path) > MAX_VISIBLE_PATH_LENGTH) {
                g_edit_cursor_x = 34 + MAX_VISIBLE_PATH_LENGTH - 1;
            } else {
                g_edit_cursor_x = 34 + strlen(g_install_path) - 1;
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
            g_exit = 1;
        default:
            break;
    };
}

int main(void) {
    int result;
    g_exit = 0;

    // result = load_manifest("TESTMANI", &g_manifest);
    // if (result != 0) {
    //     printf("Couldn't load manifest!\n");
    //     return -1;
    // }

    // set_manifest_base_path(&g_manifest, path);

    // while (!manifest_complete(&g_manifest)) {
    //     result = get_manifest_step(&g_manifest);
    //     if(result != 0) {
    //         printf("Unable to get next manifest step!\n");
    //         unload_manifest(&g_manifest);
    //         return 1;
    //     }
    //     printf("Step %d: %s\n", get_cur_manifest_step(&g_manifest), get_cur_manifest_step_cmd(&g_manifest));
    //     result = perform_manifest_step(&g_manifest);
    //     if (result != 0) {
    //         printf("Couldn't perform manifest step!\n");
    //         unload_manifest(&g_manifest);
    //         return 1;
    //     }
    //     printf("Completed step %d of %d\n", get_cur_manifest_step(&g_manifest), get_num_manifest_steps(&g_manifest));
    // }

    // unload_manifest(&g_manifest);

    // printf("Path is %s\n", path);
    // result = is_path_valid(path, 1, 3);
    // if (result == 1) {
    //     result = mkdir_recursive(path);
    //     printf("Result was %d\n", result);
    // }

    g_cur_state = STATE_MAIN_SCREEN;
    g_prev_state = STATE_MAIN_SCREEN;

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

    if (is_path_valid(g_install_path, 1, 3) == 1) {
        printf("Path %s is valid!\n", g_install_path);
    } else if (is_path_valid(g_install_path, 1, 3) == 2) {
        printf("Path %s is valid but exists!\n", g_install_path);
    } else {
        printf("Path %s is invalid!\n", g_install_path);
    }

    return 0;
}
