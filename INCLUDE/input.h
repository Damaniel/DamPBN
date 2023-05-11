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
#ifndef __INPUT_H__
#define __INPUT_H__

/**
 * A struct that represents an (x,y) coordinate.
 */
typedef struct {
  int x;
  int y;
} Position;

/**
 * Takes keypresses and performs the appropriate action based on the current
 * game state
 * 
 * @param state - the game state to process input for
 * 
 * @note the state is currently global so we may not need to use a state
 *        parameter.  Just a note to myself.
 */
void process_input(int state);

/**
 * Process input for the help state (g_cur_state = STATE_HELP)
 */
void input_state_help(void);

/**
 * Process input for the logo state (g_cur_state = STATE_LOGO)
 */
void input_state_logo(void);

/**
 * Process input for the in game state (g_cur_state = STATE_TITLE)
 */
void input_state_title(void);

/**
 * Process input for the load dialog state (g_cur_state = STATE_LOAD_DIALOG)
 */
void input_state_load_dialog(void);

/**
 * Process input for the in game state (g_cur_state = STATE_GAME)
 */
void input_state_game(void);

 /**
 * Process input for the map state (g_cur_state = STATE_MAP)
 */
void input_state_map(void);

/**
 * Process input for the options screen (g_cur_state = STATE_OPTS)
*/
void input_state_options(void);

/**
 * Process input for the complete state (g_cur_state = STATE_REPLAY)
 */
void input_state_replay(void);

/**
 * Unlocks the mouse click lockout.
 */
void update_mouse_status(void);

/**
 * Checks to see if the mouse has been clicked in the specified region.
 * 
 * @param x1 the X coordinate of the upper left extent of the region
 * @param y1 the Y coordinate of the upper left extent of the region
 * @param x2 the X coordinate of the lower right extent of the region
 * @param y2 the Y coordinate of the lower right extent of the region
 * @param lockout should future click processing be locked out
 * 
 * @return 1 if the click is in the region, 0 if not
 *
 * @note The lockout parameter, if non-zero, will prevent any further processing
 *       of mouse clicks until the mouse button has been released.  It's meant
 *       as a form of debouncing; that way, one click is associated with one
 *       event (which is what we want most of the time). 
 */
int mouse_clicked_here(int x1, int y1, int x2, int y2, int lockout);

/**
 * Process mouse and keyboard input for the palette page buttons
 */
void process_palette_press(void);

/**
 * Process mouse and keyboard input for the palette color swatch area
 */
void process_palette_color_press(void);

/**
 * Process mouse and keyboard input for the Mark button
 */
void process_mark_press(void);

/**
 * Process mouse and keyboard input for the Help button
 */
void process_help_press(void);

/**
 * Process mouse and keyboard input for the Exit button
 */
void process_exit_press(void);

/**
 * Process mouse and keyboard input for the Map button
 */
void process_map_press(void);

/**
 * Process mouse and keyboard input for the Style button
 */
void process_style_press(void);

/**
 * Process mouse and keyboard input for the Save button
 */
void process_save_press(void);

/**
 * Process mouse and keyboard input for the Load button
 */
void process_load_press(void);

/**
 * Process all keyboard-specific input related to the main game area
 * (moving the cursor, clicking on a space)
 */
void process_main_area_keyboard_input(void);

/**
 * Process all mouse-specific input related to the main game area
 * (clicking/dragging on spaces, hiding the cursor while the mouse is moving)
 */
void process_main_area_mouse_input(void);

/**
 * Handles mouse input (select item, page up, page down) on the load file
 * screen.
 */
void process_load_screen_mouse_input(void);

/**
 * Calculates new positions for cursors, indices and offsets for the two
 * columns of the load screen page
 * 
 * @param direction Which direction the menu is moving (0 = up, 1 = down)
 * @param page Should the menu move an entire page (0 = single, 1 = page)
 * @param column Which menu should be moved (0 = category, 1 = picture)
 * 
*/
void calculate_new_load_item_positions(int direction, int page, int column);

/**
 * Checks if the specified position is in the main game area
 * 
 * @param x the x coordinate of the position
 * @param y the y coordinate of the position
 * 
 * @return 1 if the location is in the game area, 0 otherwise.
*/
int is_in_game_area(int x, int y);

/**
 * Checks if the specified position is in the upper right overview area
 * 
 * @param x the x coordinate of the position
 * @param y the y coordinate of the position
 * 
 * @return 1 if the location is in the overview area, 0 otherwise.
*/
int is_in_overview_area(int x, int y);

/**
 * Processes input when the mouse interacts with the in game scroll bars
 */
void process_scroll_bar_mouse_input(void);

#endif
