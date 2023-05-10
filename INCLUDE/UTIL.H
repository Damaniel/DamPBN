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

#ifndef __UTIL_H__
#define __UTIL_H__

/**
 * A single 'square' of the image.
 */
typedef struct {
  /* Should this square even be drawn at all?*/
  char is_transparent;
  /* The color this square should be */
  char pal_entry;
  /* 0 = not filled in, x = value actually filled in */
  char fill_value;
  /* The order in which this square was *correctly* filled in */
  int  order;
  /* 0 - this square isn't correct yet.  1 = this square is correct */
  char correct;
} ColorSquare;

/**
 * An x,y pair containing the location of a correctly colored square
 * 
 * @note These are the base units of a progress file.
*/
typedef struct {
  short x;
  short y;
} OrderItem;

/**
 * A picture that the player can color in
 * 
 * @note This is the base unit of the active game - whatever the player is
 *       actively doing uses this object.
 */
typedef struct {
  unsigned char version;
  char image_name[32 + 1];
  short w;
  short h;
  unsigned char category;
  unsigned char num_colors;
  ColorSquare *pic_squares;
  OrderItem *draw_order;
  char *mistakes;
} Picture;

/**
 *  A collection of metadata regarding a picture and completion progress 
 */
typedef struct {
    char name[9];
    char category;
    short width;
    short height;
    char colors;
    int progress;
    int total;
} PictureItem;

/**
 *  A collection of metadata representing a collection of pictures 
 */
typedef struct {
    char name[9];
    int items;
} CollectionItem;

/**
 * Retrives information about a Picture file
 * 
 * @param basepath the base path of the picture files (relative to the install
 *                 directory)
 * @param filename the name of the picture file to get information about
 * @param p A pointer to the picture metadata
 */
void get_picture_metadata(char *basepath, char *filename, PictureItem *p);

/**
 * Retreives information about a progress file
 * 
 * @param basepath the base path of the progress files (relative to the install
 *                 directory)
 * @param filename the name of the progress file to get information about
 * @param p A pointer to the picture/progress metadata
*/
void get_progress_metadata(char *basepath, char *filename, PictureItem *p);

/**
 * Retreives a list of available collections 
 * 
 * @note This is done by parsing the 'res/pictures' directory.  Each directory
 *       represents a single collection.
*/
void get_collections(void);

/**
 * Retreives a and populates a list of picture files and metadata
 * 
 * @param collection The name of a collection containing 0 or more picture files
 * 
 * @note This function populates a global list (g_collection_items)
 */
void get_picture_files(char *collection);

/**
 * Dumps the player's progress to a file
 * 
 * @param p a pointer to the Picture file to save progress for
 * 
 * @return 0 on success, non-zero otherwise.
*/
int save_progress_file(Picture *p);

/**
 * Retreives and loads progress from a .pro file
 * 
 * @param p a pointer to the Picture file to load progress for
 * 
 * @return 0 on success, non-zero otherwise.
*/
int load_progress_file(Picture *p);

/**
 * Deletes the progress file associated with a picture file (if present)
 * 
 * @param filename the file name of the picture file
 * 
 * @note The filename parameter takes the name of the picture file, not the
 *       progress file.  
 */
void delete_progress_file(char *filename);

/**
 * Loads a picture file and the associated color data.
 * 
 * @param filename a path to a Picture file
 * @return a pointer to a populated Picture object.
 */
Picture *load_picture_file(char *filename);

/**
 * Frees all resources associated with a loaded Picture file
 * 
 * @param p a pointer to a Picture 
 * 
 * @note This function is safe to call on already partially or fully freed Picture
 *       objects.
 */
void free_picture_file(Picture *p);

/**
 * Checks to see if the globally loaded Picture is complete.
 * 
 * @return 1 if complete, 0 if not
 * 
 * @note 'Complete' means that the finished square count equals the total 
 *       count of squares in the picture.
*/
int check_completion(void);

/**
 * Updates the internal preview scale of the global image to ensure it's easily
 * visible on the preview and playback screens.
 */
void calculate_preview_scale(void);

/**
 * A custom handler run once per game frame
 * 
 * @note it can be used for things like elapsed time, managing animation, and
 *       so on.
 */
void int_handler(void);

/**
 *  Resets picture-specific variables to their default values
 */
void init_new_pic_defaults(void);

/**
 * Resets load dialog-specific variables to their default values
 */
void init_load_dialog_defaults(void);

/**
 * Resets various variables to their default values
 */
void init_defaults(void);

#endif
