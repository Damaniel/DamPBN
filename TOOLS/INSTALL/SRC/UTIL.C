#include "UTIL.H"

/* mkdir_recursive */
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

/* is_path_valid */
int is_path_valid(char *path, int check_disk_free, int required_free_mb) {
    char *p;
    char *backslash_delim = { "\\" };
    char *inpath;
    char drive;
    unsigned char *space, *str, *str2, *upstr;
    int path_valid, result, len;
    struct stat stat_buf;
    struct diskfree_t disk_data;
    unsigned long space_per_cluster;

    // This is ugly.
    // 
    // A valid path needs to meet the following criteria:
    //    - It has no spaces or commas in it
    //    - It starts with a drive letter, colon and backslash (i.e. absolute paths only)
    //    - No path component has excess periods
    //    - No path component has more than 8 characters as the base name or 3 characters after a period
    //    - No path component uses one of the reserved DOS file names
    //    - It does or doesn't exist (either is fine, different return values will be used for these)
    //    - It needs to be on a disk that has sufficient free space (if requested)
    //
    // I'm sure there are plenty of corner cases I'm not catching, but this is just an installer for 
    // a game.  If you want to mess up your running DOS or DOSBox instance, knock yourself out.

	// Path validity:
	// 	The path should:
	// 		- Have no spaces or commas 
    space = strstr(path, " ");
    if (space != NULL) {
        printf("Spaces in the path!\n");
        return 0;
    }
    space = strstr(path, ",");
    if (space != NULL) {
        printf("Commas in the path!\n");
        return 0;
    }

	// 		- Start with a drive letter, colon and backslash
    path_valid = 0;
    if ((path[0] >= 65 && path[0] <= 90) || (path[0] >= 97 && path[0] <=122)) {
        path_valid = 1;
    } else {
        path_valid = 0;
    }
    if(path[1] == ':' && path[2] == '\\') {
        path_valid = 1;
    } else {
        path_valid = 0;
    }

    if(!path_valid) {
        printf("Path doesn't start with a drive letter!\n");
        return 0;
    }

	// 		- Have no path components longer than 8 letters (or 12 if a period is found no later than the 9th character)
    //      - Have no path components with an invalid name 
    //          (CON, NUL, AUX, COM1, COM2, COM3, COM4, LPT1, LPT2, LPT3, LPT4, PRN, CLOCK$)
    //      - Have no path components with more than 1 period
    inpath = strdup(path);
    p = strtok(inpath, backslash_delim);
    while (p != NULL) {
        path_valid = 1;
        len = strlen(p);
        str = strstr(p, ".");
        // Check for a second period.  Any more than 1 is invalid
        if(str!=NULL) {
            str2 = strstr((str+1), ".");
            if (str2 != NULL) {
                path_valid = 0;
            }
        }
        // More than 3 characters after the period (4=3+the period)
        if(strlen(str) > 4) {
            path_valid = 0;
        }
        // No period, string longer than 8 characters
        if(str == NULL && len > 8) {
            path_valid = 0;
        }
        // A period, string longer than 12 characters
        if (str != NULL && len > 12) {
            path_valid = 0;
        }
        if (!path_valid) {
            printf("Path component invalid!\n");
            free(inpath);
            return 0;
        }

        // Any reserved DOS file name
        upstr = _strupr(p);
        if (!strcmp(upstr, "COM1") || 
            !strcmp(upstr, "COM2") ||
            !strcmp(upstr, "COM3") ||
            !strcmp(upstr, "COM4")) {
                printf("COMn found in path!\n");
                free(inpath);
                return 0;
        }
        if (!strcmp(upstr, "LPT1") || 
            !strcmp(upstr, "LPT2") ||
            !strcmp(upstr, "LPT3") ||
            !strcmp(upstr, "LPT4")) {
                printf("LPTn found in path!\n");
                free(inpath);
                return 0;
        }
        if (!strcmp(upstr, "CON") || 
            !strcmp(upstr, "NUL") ||
            !strcmp(upstr, "AUX") ||
            !strcmp(upstr, "PRN") ||
            !strcmp(upstr, "CLOCK$")) {
                printf("Invalid path name found in path!\n");
                free(inpath);
                return 0;
        }

        p = strtok(NULL, backslash_delim);
    }
    free(inpath);

	// 		- Not exist
    inpath = strdup(path);
    // If the last character of the string is a backslash, remove it
    if(inpath[strlen(inpath)-1] == '\\') {
        inpath[strlen(inpath)-1] = '\0';
        printf("Note: truncated end backslash from path\n");
    }
    result = stat(inpath, &stat_buf);
    if (result == 0) {
        if (S_ISDIR(stat_buf.st_mode)) {
            printf("Directory already exists!\n");
            free(inpath);
            return 2;
        } else {
            printf("Location exists but isn't a directoty!\n");
            free(inpath);
            return 0;
        }
    }
    free(inpath);

    // 		- Be on a disk that has sufficient free space (if disk check is enabled)
    drive = path[0];
    if (drive >= 97) {
        drive = drive - 97;
    }
    if (drive >=65 && drive <=90) {
        drive = drive - 65;
    }
    if (check_disk_free) {
        if (_dos_getdiskfree(drive+1, &disk_data) == 0) {
            space_per_cluster = disk_data.sectors_per_cluster * disk_data.bytes_per_sector;
            printf("Free space on disk = %lu bytes\n", space_per_cluster * disk_data.avail_clusters);
            if ((space_per_cluster * disk_data.avail_clusters) < (1048576*required_free_mb)) {
                printf("Insufficient disk space!\n");
                return 0;
            }
        } else {
            printf("Unable to get disk space information for drive %c!\n", drive + 65);
            return 0;
        }
    }

    return 1;
}
