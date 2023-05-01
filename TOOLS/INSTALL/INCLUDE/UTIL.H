#ifndef __UTIL_H__
#define __UTIL_H__
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <malloc.h>
#include <dos.h>

#define MKDIR_MAX_PATH_LENGTH   255

/**
 * Creates a directory, creating any parent directories required.
 *
 * This function will create a directory at the target path, recursively 
 * creating any parent directories that are needed.
 *
 * @note A positive return value will contain the value of errno at the time of the
 * error.
 * 
 * @param path The path to create.
 * @return 0 if successful, -1 for general failures, a positive value otherwise
*/
int mkdir_recursive(char *path);

/**
 * Determines whether the specified path is valid.
 * 
 * @param path The path to validate
 * @param check_disk_free Should free space be checked?
 * @param required_free_mb The minimum amount of free space (in MB) required
 * @return 0 if invalid, 1 if valid but doesn't exist, 2 if valid and does exist
*/
int is_path_valid(char *path, int check_disk_free, int required_free_mb);

#endif
