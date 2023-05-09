/* Copyright 2021-2023 Shaun Brandt
   
   Permission is hereby granted, free of charge, to any person obtaining a 
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
   DEALINGS IN THE SOFTWARE.
 */
#ifndef __RENDER_H__
#define __RENDER_H__

#define NEW_COLOR_COUNT   1
#define NEW_NUMBER_COUNT  12

/* A list of areas of the screen to update when calling render_screen() */
typedef struct {
  /* The visible part of the work area*/
  int render_main_area_squares;
  /* The palette columns on the right */
  int render_palette_area;
  /* The numbers/colors in the palette */
  int render_palette;
  /* All static UI elements */
  int render_ui_components;
  /* Menu buttons */
  int render_buttons;
  /* The overview area in the top right */
  int render_overview_display;
  /* The time/progress text at the bottom */
  int render_status_text;
  /* Update the draw cursor */
  int render_draw_cursor;
  /* Update the palette cursor */
  int render_palette_cursor;
  /* Update the scrollbars */
  int render_scrollbars;
  /* The map on the map screen */
  int render_map;
  /* Render everything - convenience function */
  int render_all;
  /* Render debug text.  Must be explicitly set or cleared */
  int render_debug;

} RenderComponents;

typedef struct {
  char update_background;
  char new_color_counter;
  char color_start_counter;
  char update_title_color;
  char color_start;
} TitleAnimation;

typedef enum {
  STYLE_SOLID,
  STYLE_DIAMOND,
  STYLE_CROSS,
  NUM_STYLES
} Style;

/**
 * Resets all of the render flags for the display.
 */
void clear_render_components(RenderComponents *c);

/**
 * Draws the logo.
 * 
 * @param dest the Bitmap to draw to
 * @param c the RenderComponents instance to consult.
 * 
 * @note RenderComponents is passed in to most render functions, but is not
 *       actually used in this one.
 */
void render_logo(BITMAP *dest, RenderComponents c);

/*=============================================================================
 * update_scrollbar_positions
 *
 * Determines where and how the scrollbars should be drawn
 *============================================================================*/

/**
 * Determines where and how the in-game scrollbars should be drawn.
 * 
 * @note The load screen has its own version of this function; this one only
 *        applies to in-game scrollbars.
 */
void update_scrollbar_positions(void);

/**
 * Draw the in game scrollbars
 * 
 * @param dest the Bitmap to render the bars to
 */
void render_scrollbars(BITMAP *dest);

/**
 * draws the scrollbars for the category and image boxes on the load screen
 * 
 * @param dest the BITMAP to render the bars to
 */
void render_load_screen_scrollbars(BITMAP *dest);

/**
 * Draws content of a specific square of the play area (either a number if the
 * square isn't filled in, otherwise a block of color representing the color
 * that has been filled in.)
 * 
 * @param dest the BITMAP to render the square to
 * @param t1_x the X offset within the image represented by the top left square
 *             of the drawing area
 * @param t1_y the Y offset within the image represented by the top left square
 *             of the drawing area
 * @param off_x the X offset (relative to the top left) to draw the square
 * @param off_y the Y offset (relative to the top left) to draw the square
 * 
 * @note t1_x and t1_y are represented as the offset within the image being 
 *       worked on, while off_x and off_y are relative to the top left corner of
 *       the play area, treating it as (0, 0).  This way, we can get the a
 *       appropriate region of the image to render and the right place on
 *       sreen to put it. 
*/
void render_main_area_square_at(BITMAP *dest, int tl_x, int tl_y,
                               int off_x, int off_y);

/**
 * Draws the content (i.e number/color) of a specific index of the palette.
 * 
 * @param dest the BITMAP to draw to
 * @param palette_index the index of the palette (0-32 to draw)
 * @param change_page if set, toggle the palette page before drawing the new
 *                    value
*/
void render_palette_item_at(BITMAP *dest, int palette_index, int change_page);

/**
 * Draws the status text in the lower portion of the screen 
 * 
 * @param dest the BITMAP to draw to
 */
void render_status_text(BITMAP *dest);

/**
 * Draws all components that aren't dynamic somehow
 *
 * @param dest the BITMAP to draw to
 */
void render_primary_ui(BITMAP *dest);

/**
 * Draws all buttons in the lower right corner of the screen
 * 
 * @param dest the BITMAP to draw to
 */
void render_menu_buttons(BITMAP *dest);

/**
 * Draws screen components when the game is in the STATE_MAP state.
 * 
 * @param dest the BITMAP to draw to
 * @param c a list of render components to reference
 */
void render_map_screen(BITMAP *dest, RenderComponents c);

/**
 * Draws screen components when the game is in the STATE_TITLE state.
 * 
 * @param dest the BITMAP to draw to
 * @param c a list of render components to reference
 */
void render_title_screen(BITMAP *dest, RenderComponents c);

/**
 * Draws screen components when the game is in the STATE_GAME state.
 * 
 * @param dest the BITMAP to draw to
 * @param c a list of render components to reference
 */
void render_game_screen(BITMAP *dest, RenderComponents c);

/**
 * Draws screen components.  The components that are drawn is dictated by
 * the current state and the global RenderComponents object.
 * 
 * @param dest the BITMAP to draw to
 * @param c a list of render components to reference
 */
void render_screen(BITMAP *dest, RenderComponents c);

/**
 * Gets the width of a proportional string.
 *
 * @param text the text to analyze
 * @return the width of the string (in pixels) when using the proportional font
 */
int get_prop_text_width(char *text);

/**
 * Writes a string centered at 'center' using the proportional font.
 * 
 * @param dest the BITMAP to draw to
 * @param test the text to render
 * @param center the center (X) position of the location to place the string
 * @param y_pos the Y position of the location to place the string
 */
void render_centered_prop_text(BITMAP *dest, char *text, int center, int y_pos);

/**
 * Writes a string using the proportional font
 *
 * @param destination the BITMAP to draw to
 * @param text the text to render
 * @param x_pos the X position to place the beginning of the string
 * @param y_pos the Y position to place the string 
 */
void render_prop_text(BITMAP *destination, char *text, int x_pos, int y_pos);

/**
 * Displays the 'load picture' dialog
 *
 * @param dest the BITMAP to draw to
 * @param c a list of render components to reference
 */
void render_load_dialog(BITMAP *dest, RenderComponents c);

/**
 * Displays the 'saving' message
 *
 * @param dest the BITMAP to draw to
 * @param c a list of render components to reference
 */
void render_save_message(BITMAP *dest, RenderComponents c);

/**
 * Displays the 'loading' message
 * 
 * @param dest the BITMAP to draw to
 * @param c a list of render components to reference
 */
void render_load_message(BITMAP *dest, RenderComponents c);

/**
 * Displays the current help page
 * 
 * @param dest the BITMAP to draw to
 * @param c a list of render components to reference
 */
void render_help_text(BITMAP *dest, RenderComponents c);

/**
 * Displays the replay
 *
 * @param dest the BITMAP to draw to
 * @param c a list of render components to reference
 */
void render_replay_state(BITMAP *dest, RenderComponents c);

/**
 * Draws the draw cursor in the correct place on the screen
 *
 * @param dest the BITMAP to draw to
 */
void render_draw_cursor(BITMAP *dest);

/**
 * Update the underlying overview area bitmap. 
 * 
 * @note Used to seed the entire thing after loading an in-progress picture
 */
void update_overview_area(void);

/**
 * Update a single block (4x4 pixels) of the overview area.  
 * 
 * @param i the horizontal group of 4 pixels starting at (i*4)
 * @param j the vertical group of 4 pixels starting at (j*4)
 * 
 * @note Used by update_overview_area and called when a block is placed somewhere
 */
void update_overview_area_at(int i, int j);

/**
 * Load title graphics.
 */
int load_title(void);

/**
 * Load logo graphics.
 */
int load_logo(void);

/**
 * Destroy bitmaps created with create_bitmap()
 */
void free_graphics(void);

/**
 * Load in-game graphics into bitmap objects.  All graphics are stored in the
 * PCX format.
 */
int load_graphics(void);

/**
 * Fills each square of the title background with a random color from the 
 * palette
 * 
 * @param dest the BITMAP to render the data to
 */
void render_title_fill_random_bg(BITMAP *dest);

/**
 * Forces a change of palette and clears the screen to eliminate corrupted graphics
 * in logo->title state changes on slower hardware
 * 
 * Note that this is mainly an issue on hardware at the lower end of the supported
 * CPU range (i.e. slower 386 systems).  Said systems actually take a non-trivial
 * amount of time to load resources/graphics/etc, so we want the screen clear and
 * palette ready even before we start loading things.
*/
void render_force_clear(void);
#endif
