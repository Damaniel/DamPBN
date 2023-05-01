#ifndef __UTIL_H__
#define __UTIL_H__

#define MKDIR_MAX_PATH_LENGTH   255

/*
 * mkdir_recursive - creates a folder at <path>, and all parent subdirectories
 *                   if they don't already exist.
 */
int mkdir_recursive(char *path);

#endif
