#include "UTIL.H"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <direct.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <malloc.h>

/*
 * mkdir_recursive
 */
int mkdir_recursive(char *path) {
    char *inpath;
    char cur_dir_path[MKDIR_MAX_PATH_LENGTH];
    char *p;
    char *delim = {"\\"};
    int length = 0, segments = 0, result;
    struct stat stat_buf;

    memset(cur_dir_path, '\0', MKDIR_MAX_PATH_LENGTH);    

    // Use a copy of the path string since we need to modify it
    inpath = strdup(path);

    // If the last character of the string is a backslash, remove it
    if(inpath[strlen(inpath)-1] == '\\') {
        inpath[strlen(inpath)-1] = '\0';
        printf("Note: truncated end backslash from path\n");
    }

    // Check if the path already exists and return if it does.
    // If it exists and is a directory, return OK - the path is already there.
    // If it exists and isn't a directory, return an error.
    result = stat(inpath, &stat_buf);
    if (result != 0) {
        printf("Directory %s doesn't exist - yet\n", inpath);
    } else {
        if (S_ISDIR(stat_buf.st_mode)) {
            printf("Path %s exists and is a directory. We're done.\n", inpath);
            free(inpath);
            return 0;
        }
        else {
            printf("Path %s exists and is *not* a directory. Illegal!\n", inpath);
            free(inpath);
            return errno;
        }
    }

    p = strtok(inpath, delim);
    while (p != NULL) {
        // Increment the number of tokens
        segments = segments+1;
        // Add the latest token to the dir path
        strncat(cur_dir_path, p, MKDIR_MAX_PATH_LENGTH - length);
        length += strlen(p);
        // If we finally have a path, then start trying to make it
        if (segments >= 2) {
            result = stat(cur_dir_path, &stat_buf);
            // If the directory doesn't already exist, create it
            if (result != 0) {
                printf("Creating path %s\n", cur_dir_path);
                result = mkdir(cur_dir_path);
                if (result != 0) {
                    // Making the directory failed for some reason
                    printf("Couldn't create the specified path (%s)\n", inpath);
                    free(inpath);
                    return errno;
                }
            }
            // If it does, just skip this time around
            else {
                printf("Skipping %s - path presumably exists\n", cur_dir_path);
            }
        }
        // Add a separator before we tack on another path element
        strncat(cur_dir_path, "\\", 1);
        length = length + 1;
        // Grab another token
        p = strtok(NULL, delim);
        // If the string is too long, return an error rather than truncate
        if (length > MKDIR_MAX_PATH_LENGTH) {
            printf("Can't make more directories; path is too long");
            free(inpath);
            return -1;
        }
    }
    // If segments < 2, we made no paths
    if(segments < 2) {
        printf("Can't make a directory with less than 2 segments!\n");
        free(inpath);
        return -1;
    }

    // Return 'success'
    free(inpath);
    return 0;
}
