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
}

void clear_render_components(void) {
    g_render_components.intro_window = 0;
    g_render_components.background = 0;
    g_render_components.destination_edit = 0;
    g_render_components.top_status_text = 0;
    g_render_components.bottom_status_text = 0;
    g_render_components.error_message = 0;
}

void render_main_screen(void) {
    if (g_render_components.background) {
        fill_box_at(0, 0, 79, 24, 177, g_render_colors.background);
        hline_at(0, 0, 80, ' ', g_render_colors.status_bar);
        hline_at(0, 24, 80, ' ', g_render_colors.status_bar);
        g_render_components.background = 0;
    }
    if (g_render_components.top_status_text) {
        string_at(29, 0, "DamPBN Installer v0.10", g_render_colors.status_text);
        g_render_components.top_status_text = 0;
    }
    if (g_render_components.bottom_status_text) {
        string_at(26, 24, "Copyright 2023 Shaun Brandt", g_render_colors.status_text);
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
        string_at(34, 18, "                        ", g_render_colors.edit_box);
        string_at(58, 18, " ", g_render_colors.box_text);
        g_render_components.destination_edit_area = 0;
    }

    if (g_render_components.destination_edit) {
        string_at(34, 18, g_install_path, g_render_colors.edit_box);
        char_at(g_edit_cursor_x, g_edit_cursor_y, ' ', g_render_colors.edit_text);
        g_render_components.destination_edit = 0;
    }
}

void render(void) {
    switch (g_cur_state) {
        case STATE_MAIN_SCREEN:
            render_main_screen();
            break;
    };
}

