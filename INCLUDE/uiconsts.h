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
#ifndef __UI_CONSTS_H__
#define __UI_CONSTS_H__
 
 /* Values for all UI positional constants.  Avoids magic numbers and makes
    it clear where things go on screen. */

/*==============================================
 * General 
 *==============================================*/
#define NUMBER_BOX_WIDTH            11
#define NUMBER_BOX_HEIGHT           11
#define NUMBER_BOX_INTERIOR_WIDTH    9
#define NUMBER_BOX_INTERIOR_HEIGHT   9

/* Boxes are 11, offsets are 10.  This is because the boxes are drawn 
   overlapping (so there's only one shared border pixel between 2
   adjacent boxes */
#define NUMBER_BOX_RENDER_X_OFFSET  10
#define NUMBER_BOX_RENDER_Y_OFFSET  10

#define DRAW_AREA_X                  2
#define DRAW_AREA_Y                  2

#define DRAW_AREA_WIDTH            200
#define DRAW_AREA_HEIGHT           160

/*==============================================
 * High-level elements
 *==============================================*/
#define RIGHT_SIDE_PANEL_X         209
#define RIGHT_SIDE_PANEL_Y           0

#define BOTTOM_PANEL_X               0
#define BOTTOM_PANEL_Y             169

#define MAIN_AREA_X                  0
#define MAIN_AREA_Y                  0

/*==============================================
 * Palette area 
 *==============================================*/
#define NUM_PALETTE_COLUMNS          4
#define NUM_PALETTE_ROWS             8

#define PALETTE_PAGE_1_START         0
#define PALETTE_PAGE_2_START        32

#define PALETTE_BOX_WIDTH            6
#define PALETTE_BOX_HEIGHT          11
#define PALETTE_BOX_INTERIOR_WIDTH   4
#define PALETTE_BOX_INTERIOR_HEIGHT  9
#define PALETTE_ENTRY_WIDTH         16
#define PALETTE_ENTRY_HEIGHT        10

#define PALETTE_AREA_X             226
#define PALETTE_AREA_Y              83

#define SWATCH_AREA_X              236
#define SWATCH_AREA_Y               83

#define PALETTE_COLUMN_WIDTH        20
#define PALETTE_ITEM_HEIGHT         10

#define PALETTE_COLUMN_1_X         226
#define PALETTE_COLUMN_2_X         246
#define PALETTE_COLUMN_3_X         266
#define PALETTE_COLUMN_4_X         286
#define PALETTE_COLUMN_Y            83

/*==============================================
 * Buttons
 *==============================================*/
#define PAGE_1_BUTTON_X            237
#define PAGE_1_BUTTON_Y             69
#define PAGE_2_BUTTON_X            266
#define PAGE_2_BUTTON_Y             69
#define PAGE_BUTTON_WIDTH           25
#define PAGE_BUTTON_HEIGHT          11

/*==============================================
 * Cursors
 *==============================================*/
#define DRAW_CURSOR_WIDTH           10
#define DRAW_CURSOR_HEIGHT          10
#define PALETTE_CURSOR_WIDTH        16
#define PALETTE_CURSOR_HEIGHT       11

#define CATEGORY_TEXT_X              5
#define CATEGORY_TEXT_Y            172

#define ELAPSED_TEXT_X              69
#define ELAPSED_TEXT_Y             190

#define SIZE_TEXT_X                133
#define SIZE_TEXT_Y                172

#define MISTAKES_X                 133
#define MISTAKES_Y                 181

#define PROGRESS_X                   5
#define PROGRESS_Y                 181

#define X_SCROLLBAR_AREA_WIDTH     199
#define X_SCROLLBAR_AREA_HEIGHT      4
#define X_SCROLLBAR_AREA_X           3
#define X_SCROLLBAR_AREA_Y         163

#define Y_SCROLLBAR_AREA_WIDTH       4
#define Y_SCROLLBAR_AREA_HEIGHT    159
#define Y_SCROLLBAR_AREA_X         203
#define Y_SCROLLBAR_AREA_Y           3

#define SCROLLBAR_BG_COLOR         192
#define SCROLLBAR_INTERIOR_COLOR   202
#define SCROLLBAR_BORDER_COLOR     208

/* The 'Saving...' message when you press S while working on a picture */
#define SAVING_MESSAGE_X           144
#define SAVING_MESSAGE_Y           146

/* The 'Loading...' message when you've selected a picture to load */
#define LOADING_MESSAGE_X          138
#define LOADING_MESSAGE_Y          146

/* The load picture dialog */
#define LOAD_DIALOG_X               56
#define LOAD_DIALOG_Y               23

/* Locations of the highlights for the collection and image sections
   of the load dialog */
#define COLLECTION_HIGHLIGHT_X_OFF     ((LOAD_DIALOG_X) + 4)
#define COLLECTION_HIGHLIGHT_Y_OFF     ((LOAD_DIALOG_Y) + 26)
#define COLLECTION_HIGHLIGHT_WIDTH     58
#define COLLECTION_HIGHLIGHT_HEIGHT    94

#define IMAGE_HIGHLIGHT_X_OFF          ((LOAD_DIALOG_X) + 65)
#define IMAGE_HIGHLIGHT_Y_OFF          ((LOAD_DIALOG_Y) + 26)
#define IMAGE_HIGHLIGHT_WIDTH          58
#define IMAGE_HIGHLIGHT_HEIGHT         94

/* Position and size of the first collection name item */
#define LOAD_COLLECTION_NAME_X_OFF        ((LOAD_DIALOG_X) + 6)
#define LOAD_COLLECTION_NAME_Y_OFF        ((LOAD_DIALOG_Y) + 28)
#define LOAD_COLLECTION_NAME_WIDTH        49 
#define LOAD_COLLECTION_NAME_HEIGHT        9

/* Position and size of the first file name item */
#define LOAD_FILE_NAME_X_OFF        ((LOAD_DIALOG_X) + 67)
#define LOAD_FILE_NAME_Y_OFF        ((LOAD_DIALOG_Y) + 28)
#define LOAD_FILE_NAME_WIDTH        49 
#define LOAD_FILE_NAME_HEIGHT        9

/* How many files can we see at a time? */
#define LOAD_NUM_VISIBLE_FILES      10

/* The position of the top of the file selector scrollbar */
#define LOAD_FILE_CATEGORY_SCROLLBAR_X       ((LOAD_DIALOG_X) + 55)
#define LOAD_FILE_PICTURE_SCROLLBAR_X       ((LOAD_DIALOG_X) + 117)
#define LOAD_FILE_SCROLLBAR_Y       ((LOAD_DIALOG_Y) + 28)

/* The width of the scrollbar.  The height and y position of the actual 
   bar are dynamic, so are defined via variables */
#define LOAD_FILE_SCROLLBAR_WIDTH    4
#define LOAD_FILE_SCROLLBAR_AREA_HEIGHT      90

/* The dimensions and sizes of the boxes that hold Picture metadata */

#define LOAD_FILE_CATEGORY_X         ((LOAD_DIALOG_X) + 130)
#define LOAD_FILE_CATEGORY_Y         ((LOAD_DIALOG_Y) + 32)
#define LOAD_FILE_CATEGORY_WIDTH     72
#define LOAD_FILE_CATEGORY_HEIGHT     9
#define LOAD_FILE_CATEGORY_TEXT_X    ((LOAD_DIALOG_X) + 166)
#define LOAD_FILE_CATEGORY_TEXT_Y    ((LOAD_DIALOG_Y) + 33)

#define LOAD_FILE_XSIZE_X            ((LOAD_DIALOG_X) + 130)
#define LOAD_FILE_XSIZE_Y            ((LOAD_DIALOG_Y) + 55)
#define LOAD_FILE_XSIZE_WIDTH        29
#define LOAD_FILE_XSIZE_HEIGHT        9
#define LOAD_FILE_XSIZE_TEXT_X       ((LOAD_DIALOG_X) + 145)
#define LOAD_FILE_XSIZE_TEXT_Y       ((LOAD_DIALOG_Y) + 56)

#define LOAD_FILE_YSIZE_X            ((LOAD_DIALOG_X) + 173)
#define LOAD_FILE_YSIZE_Y            ((LOAD_DIALOG_Y) + 55)
#define LOAD_FILE_YSIZE_WIDTH        29
#define LOAD_FILE_YSIZE_HEIGHT        9
#define LOAD_FILE_YSIZE_TEXT_X       ((LOAD_DIALOG_X) + 188)
#define LOAD_FILE_YSIZE_TEXT_Y       ((LOAD_DIALOG_Y) + 56)

#define LOAD_FILE_COLORS_X           ((LOAD_DIALOG_X) + 130)
#define LOAD_FILE_COLORS_Y           ((LOAD_DIALOG_Y) + 78)
#define LOAD_FILE_COLORS_WIDTH       72
#define LOAD_FILE_COLORS_HEIGHT       9
#define LOAD_FILE_COLORS_TEXT_X      ((LOAD_DIALOG_X) + 166)  
#define LOAD_FILE_COLORS_TEXT_Y      ((LOAD_DIALOG_Y) + 79)

#define LOAD_FILE_PROGRESS_X         ((LOAD_DIALOG_X) + 130)
#define LOAD_FILE_PROGRESS_Y         ((LOAD_DIALOG_Y) + 101)
#define LOAD_FILE_PROGRESS_WIDTH     72
#define LOAD_FILE_PROGRESS_HEIGHT     9
#define LOAD_FILE_PROGRESS_TEXT_X    ((LOAD_DIALOG_X) + 166)   
#define LOAD_FILE_PROGRESS_TEXT_Y    ((LOAD_DIALOG_Y) + 102)

#define LOAD_FILE_EXTRA_X             59
#define LOAD_FILE_EXTRA_Y            166

#define LOAD_FILE_EXTRA_WIDTH        201
#define LOAD_FILE_EXTRA_HEIGHT         8

#define LOAD_FILE_EXTRA_CENTER_X (LOAD_FILE_EXTRA_X + (LOAD_FILE_EXTRA_WIDTH / 2))

#define LOAD_RESET_CONFIRM_X          120
#define LOAD_RESET_CONFIRM_Y           87

/* Pick the button set depending on whether a button  is pressed or not */
#define BUTTON_DEFAULT_OFFSET      0
#define BUTTON_PRESSED_OFFSET      22

/* The size of a menu button */
#define MENU_BUTTON_WIDTH         25
#define MENU_BUTTON_HEIGHT        11

/* Offsets of the button within the source bitmap */
#define SAVE_BUTTON_X_OFFSET       0
#define SAVE_BUTTON_Y_OFFSET       0

#define STYLE_BUTTON_X_OFFSET     25
#define STYLE_BUTTON_Y_OFFSET      0

#define OPTS_BUTTON_X_OFFSET      50
#define OPTS_BUTTON_Y_OFFSET       0

#define HELP_BUTTON_X_OFFSET      75
#define HELP_BUTTON_Y_OFFSET       0

#define LOAD_BUTTON_X_OFFSET       0
#define LOAD_BUTTON_Y_OFFSET      11

#define MARK_BUTTON_X_OFFSET      25
#define MARK_BUTTON_Y_OFFSET      11

#define MAP_BUTTON_X_OFFSET       50
#define MAP_BUTTON_Y_OFFSET       11

#define EXIT_BUTTON_X_OFFSET      75
#define EXIT_BUTTON_Y_OFFSET      11

/* Positions where the buttons go on the screen itself */
#define SAVE_BUTTON_X              215
#define SAVE_BUTTON_Y              174

#define STYLE_BUTTON_X             239
#define STYLE_BUTTON_Y             174

#define OPTS_BUTTON_X              263
#define OPTS_BUTTON_Y              174

#define HELP_BUTTON_X              287
#define HELP_BUTTON_Y              174

#define LOAD_BUTTON_X              215
#define LOAD_BUTTON_Y              184

#define MARK_BUTTON_X              239
#define MARK_BUTTON_Y              184

#define MAP_BUTTON_X               263
#define MAP_BUTTON_Y               184

#define EXIT_BUTTON_X              287
#define EXIT_BUTTON_Y              184

#define OVERVIEW_BLOCK_SIZE          4
#define OVERVIEW_WIDTH              80
#define OVERVIEW_HEIGHT             50
#define OVERVIEW_X                 224
#define OVERVIEW_Y                  10

#define FINISHED_X                 0
#define FINISHED_Y                 185

#define MOVE_UP                    0
#define MOVE_DOWN                  1
#define MOVE_SINGLE                0
#define MOVE_PAGE                  1
#define MOVE_COLLECTION            0
#define MOVE_IMAGE                 1

/* Option screen defines */

#define OPTION_SCREEN_X             63
#define OPTION_SCREEN_Y             31
#define OPTION_SCREEN_W             194
#define OPTION_SCREEN_H             130

#define OPTION_HEADER_X             128
#define OPTION_HEADER_Y             37

#define OPTION_CURSOR_MARGIN        2
#define OPTION_CURSOR_INNER_MARGIN  1

#define SOUND_MENU_X                71
#define SOUND_MENU_Y                54
#define SOUND_MENU_W                31
#define SOUND_MENU_H                 7

#define SOUND_ON_X                  120
#define SOUND_ON_Y                  54
#define SOUND_ON_OPT_X              119
#define SOUND_ON_OPT_Y              62
#define SOUND_ON_OPT_W              12

#define SOUND_OFF_X                 153
#define SOUND_OFF_Y                 54
#define SOUND_OFF_OPT_X             152
#define SOUND_OFF_OPT_Y             62
#define SOUND_OFF_OPT_W             16

#define SOUND_VOL_MENU_X            77
#define SOUND_VOL_MENU_Y            66
#define SOUND_VOL_MENU_W            35
#define SOUND_VOL_MENU_H            7
#define SOUND_VOL_MINUS_X           134
#define SOUND_VOL_MINUS_Y           66
#define SOUND_VOL_MINUS_W           9
#define SOUND_VOL_MINUS_H           9
#define SOUND_VOL_PLUS_X            209
#define SOUND_VOL_PLUS_Y            66
#define SOUND_VOL_PLUS_W            9
#define SOUND_VOL_PLUS_H            9

#define SOUND_BAR_START_X           145
#define SOUND_BAR_START_Y           67
#define SOUND_BAR_BAR_W             2
#define SOUND_BAR_BAR_H             5
#define SOUND_BAR_NUM_BARS          16
#define SOUND_BAR_X_GAP             2

#define MUSIC_MENU_X                71
#define MUSIC_MENU_Y                80
#define MUSIC_MENU_W                28
#define MUSIC_MENU_H                7

#define MUSIC_ON_X                  120
#define MUSIC_ON_Y                  80
#define MUSIC_ON_OPT_X              119
#define MUSIC_ON_OPT_Y              88
#define MUSIC_ON_OPT_W              12

#define MUSIC_OFF_X                 153
#define MUSIC_OFF_Y                 80
#define MUSIC_OFF_OPT_X             152
#define MUSIC_OFF_OPT_Y             88
#define MUSIC_OFF_OPT_W             16

#define MUSIC_VOL_MENU_X            77
#define MUSIC_VOL_MENU_Y            92
#define MUSIC_VOL_MENU_W            35
#define MUSIC_VOL_MENU_H            7
#define MUSIC_VOL_MINUS_X           134
#define MUSIC_VOL_MINUS_Y           92
#define MUSIC_VOL_MINUS_W           9
#define MUSIC_VOL_MINUS_H           9
#define MUSIC_VOL_PLUS_X            209
#define MUSIC_VOL_PLUS_Y            92
#define MUSIC_VOL_PLUS_W            9
#define MUSIC_VOL_PLUS_H            9

#define MUSIC_BAR_START_X           145
#define MUSIC_BAR_START_Y           94
#define MUSIC_BAR_BAR_W             2
#define MUSIC_BAR_BAR_H             5
#define MUSIC_BAR_NUM_BARS          16
#define MUSIC_BAR_X_GAP             2

#define AUTOSAVE_MENU_X             71
#define AUTOSAVE_MENU_Y             109
#define AUTOSAVE_MENU_W             49
#define AUTOSAVE_MENU_H             7

#define AUTOSAVE_OFF_X              133
#define AUTOSAVE_OFF_Y              109
#define AUTOSAVE_OFF_OPT_X          132
#define AUTOSAVE_OFF_OPT_Y          117
#define AUTOSAVE_OFF_OPT_W          16

#define AUTOSAVE_1M_X               158
#define AUTOSAVE_1M_Y               109
#define AUTOSAVE_1M_OPT_X           157  
#define AUTOSAVE_1M_OPT_Y           117
#define AUTOSAVE_1M_OPT_W           12

#define AUTOSAVE_2M_X               179
#define AUTOSAVE_2M_Y               109
#define AUTOSAVE_2M_OPT_X           178
#define AUTOSAVE_2M_OPT_Y           117
#define AUTOSAVE_2M_OPT_W           12

#define AUTOSAVE_5M_X               200
#define AUTOSAVE_5M_Y               109
#define AUTOSAVE_5M_OPT_X           199
#define AUTOSAVE_5M_OPT_Y           117
#define AUTOSAVE_5M_OPT_W           12

#define AUTOSAVE_10M_X              221
#define AUTOSAVE_10M_Y              109
#define AUTOSAVE_10M_OPT_X          220
#define AUTOSAVE_10M_OPT_Y          117
#define AUTOSAVE_10M_OPT_W          18

#define SAVE_ON_EXIT_MENU_X         71
#define SAVE_ON_EXIT_MENU_Y         125
#define SAVE_ON_EXIT_MENU_W         64
#define SAVE_ON_EXIT_MENU_H         7

#define SAVE_ON_EXIT_YES_X          149
#define SAVE_ON_EXIT_YES_Y          125
#define SAVE_ON_EXIT_YES_OPT_X      148
#define SAVE_ON_EXIT_YES_OPT_Y      133
#define SAVE_ON_EXIT_YES_OPT_W       18
#define SAVE_ON_EXIT_NO_X           189
#define SAVE_ON_EXIT_NO_Y           125
#define SAVE_ON_EXIT_NO_OPT_X       188
#define SAVE_ON_EXIT_NO_OPT_Y       133   
#define SAVE_ON_EXIT_NO_OPT_W       12

#define OPT_OK_X                    154
#define OPT_OK_Y                    145
#define OPT_OK_W                    11
#define OPT_OK_H                    7

#endif 
 