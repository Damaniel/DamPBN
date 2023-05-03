#include "manifest.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// About manifest files
//
// The manifest file contains the following:
//  - One line that specifies the number of commands in the file
//  - A series of lines, each consisting of one command:
//    - MKDIR - makes the directory specified, creating all parent directories if needed
//    - COPY - copies a file to the specified destination directory
//    - COPYDIR - copies the contents of the specified directory to the specified destination directory
//
//  Notes:
//    COPYDIR will assume that all paths up to the last have been created.  The last directory path
//    of the source will be created at the destination.  For example:
//
//      - COPY a\b c\d\b will copy the contents of A\B to C\D\B
//      - COPY A\B C\D will copy the contents of A\B to C\D
//
//    Any tools that create the manifest file will explicitly ensure that the final part of the source
//    and destination paths match, so that the tree is created correctly.
//
Manifest g_manifest;

/* load_manifest */
int load_manifest(char *manifest_file, Manifest *m) {
    char line[MAX_MANIFEST_STEP_LEN];
    char *result;

    m->manifest_fp = fopen(manifest_file, "r");
    if (m->manifest_fp == NULL) {
        //printf("Manifest file not found!\n");
        return -1;
    }
    result = fgets(line, MAX_MANIFEST_STEP_LEN, m->manifest_fp);
    if (result == NULL) {
        //printf("Couldn't get manifest step count!\n");
        return -1;
    }

    m->num_steps = atoi(line);
    if (m->num_steps <1) {
        //printf("No step count provided!\n");
        return -1;
    }

    //printf("Manifest has %d steps\n", m->num_steps);
    return 0;
}

/* unload_manifest */
int unload_manifest(Manifest *m) {
    fclose(m->manifest_fp);
    return 0;
}

/* get_manifest_step */
int get_manifest_step(Manifest *m) {
    char *result, *p, *cur_step;    
    char *delim = {" "};
    char step[MAX_MANIFEST_STEP_LEN];
    int i;

    // read the next step from the manifest
    result = fgets(step, MAX_MANIFEST_STEP_LEN, m->manifest_fp);

    if (m->manifest_fp == NULL) {
        if (m->cur_step_idx + 1 == m->num_steps) {
            //printf("Last step complete!\n");
            return 0;
        } else {
            //printf("Step count doesn't match (%d expected, %d performed)\n", m->num_steps, m->cur_step_idx + 1);
            return 1;
        }
    }
    
    // Strip out newlines, if any (they should be at the end)
    for(i=0;i<strlen(step);i++) {
        if (step[i] == '\n' || step[i] == '\r') {
            step[i] = '\0';
        }
    }

    cur_step = strdup(step);
    // Parse the cmd
    p = strtok(cur_step, delim);
    if (!strcmp(p, "MKDIR")) {
        m->ms.operation = MKDIR;
    } else if (!strcmp(p, "COPYDIR")) {
        m->ms.operation = COPYDIR;
    } else if (!strcmp(p, "COPY")) {
        m->ms.operation = COPY;
    } else {
        //printf("Unknown command!\n");
        free(cur_step);
        return 1;
    }

    // Parse the source
    p = strtok(NULL, delim);
    strncpy(m->ms.source, p, 40);
    // Parse the destination, if any
    if(m->ms.operation != 0) {
        p = strtok(NULL, delim);
        strncpy(m->ms.dest, p, 40);
    }
 
    strncpy(m->cur_step_cmd, step, MAX_MANIFEST_STEP_LEN);
    m->cur_step_idx = m->cur_step_idx + 1;
    return 0;
}

/* manifest_complete */
int manifest_complete(Manifest *m) {
    if (m->cur_step_idx != m->num_steps) {
        return 0;
    }
    return 1;
}

/* perform_manifest_step */
int perform_manifest_step(Manifest *m) {
    char source_path[MKDIR_MAX_PATH_LENGTH];
    char dest_path[MKDIR_MAX_PATH_LENGTH];
    char command[MKDIR_MAX_PATH_LENGTH];

    int result;

    if (m->ms.operation == MKDIR) {
        strncpy(source_path, m->base_path, MAX_MANIFEST_PATH_LEN);
        strncat(source_path, "\\", 1);
        strncat(source_path, m->ms.source, 40);
    } else {
        strncpy(source_path, m->ms.source, 40);
    }    
    if (m->ms.operation != MKDIR) {
        strncpy(dest_path, m->base_path, MAX_MANIFEST_PATH_LEN);
        strncat(dest_path, "\\", 1);
        strncat(dest_path, m->ms.dest, 40);
    }

    switch(m->ms.operation) {
        case MKDIR:
            result = mkdir_recursive(source_path);
            if (result != 0) {
                //printf("MKDIR step failed making %s!\n", source_path);
                return -1;
            } else {
                //printf("Created directory %s\n", source_path);
            }
            break;
        case COPY:
            memset(command, '\0', MKDIR_MAX_PATH_LENGTH);
            strncpy(command, "COPY ", 5);
            strncat(command, source_path, MKDIR_MAX_PATH_LENGTH);
            strncat(command, " ", 1);
            strncat(command, dest_path, MKDIR_MAX_PATH_LENGTH);
            strncat(command, " >NUL", 5);
            //printf("COPY command is '%s'\n", command);
            result = system(command);
            //printf("  Result of system is %d\n", result);
            break;
        case COPYDIR:
            memset(command, '\0', MKDIR_MAX_PATH_LENGTH);
            strncpy(command, "XCOPY ", 6);
            strncat(command, source_path, MKDIR_MAX_PATH_LENGTH);
            strncat(command, " ", 1);
            strncat(command, dest_path, MKDIR_MAX_PATH_LENGTH);
            strncat(command, " /E /Y >NUL", 20);
            //printf("COPYDIR command is '%s'\n", command);
            result = system(command);
            //printf("  Result of system is %d\n", result);
            break;
        default:
            //printf("Warning - unknown operation %d\n", m->ms.operation);
            break;
    }
    return 0;
}

/* get_num_manifest_steps */
int get_num_manifest_steps(Manifest *m) {
    return m->num_steps;
}

/* get_cur_manifest_step */
int get_cur_manifest_step(Manifest *m) {
    return m->cur_step_idx;
}

/* get_cur_manifest_step_cmd */
char *get_cur_manifest_step_cmd(Manifest *m) {
    return m->cur_step_cmd;
}

/* set_manifest_base_path */
void set_manifest_base_path(Manifest *m, char *path) {
    strncpy(m->base_path, path, MAX_MANIFEST_PATH_LEN);
}
