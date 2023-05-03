#ifndef __RENDER_H__
#define __RENDER_H__

#include "INSTALL.H"

void init_render_colors(void);
void clear_render_components(void);
void render_confirm_existing_screen(void);
void render_main_screen(void);
void render_invalid_path_screen(void);
void render(void);
void render_path_text(int left_offset);
char get_letter_under_cursor(int cursor_pos, int left_offset);
void set_letter_under_cursor(int cursor_pos, int left_offset, char c);

#define MAX_VISIBLE_PATH_LENGTH     24
#define PATH_EDIT_BOX_X             34

typedef struct {
    int background;
    int intro_window;
    int destination_edit_area;
    int destination_edit;
    int top_status_text;
    int bottom_status_text;
    int error_message;
    int confirm_existing_message;
    int debug_text;
} RenderComponents;

typedef struct {
    char background;
    char status_bar;
    char status_text;
    char box_edge;
    char box_text;
    char edit_box;
    char edit_text;
    char error_box;
    char error_text;
} RenderColors;

#endif
