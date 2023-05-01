#ifndef __RENDER_H__
#define __RENDER_H__

#include "INSTALL.H"

void init_render_colors(void);
void clear_render_components(void);
void render_main_screen(void);
void render(void);


typedef struct {
    int background;
    int intro_window;
    int destination_edit_area;
    int destination_edit;
    int top_status_text;
    int bottom_status_text;
    int error_message;
} RenderComponents;

typedef struct {
    char background;
    char status_bar;
    char status_text;
    char box_edge;
    char box_text;
    char edit_box;
    char edit_text;
} RenderColors;

#endif
