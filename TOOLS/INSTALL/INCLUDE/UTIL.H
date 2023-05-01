#ifndef __UTIL_H__
#define __UTIL_H__

#define MKDIR_MAX_PATH_LENGTH   255

/*
 * mkdir_recursive - creates a folder at <path>, and all parent subdirectories
 *                   if they don't already exist.
 */
int mkdir_recursive(char *path);

/*
 * is_path_valid - determines whether the specified path is a valid one.
 *                 Returns 1 if valid, 0 if not. 
 */
int is_path_valid(char *path, int check_disk_free, int required_free_mb);

#endif
