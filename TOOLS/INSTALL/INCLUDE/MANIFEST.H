#ifndef __MANIFEST_H__
#define __MANIFEST_H__
#include <stdio.h>

#define MAX_MANIFEST_STEP_LEN      128
#define MAX_MANIFEST_PATH_LEN      64

typedef enum {
    MKDIR,
    COPY,
    COPYDIR
} ManifestCmd;

typedef struct {
    ManifestCmd operation;
    char source[40];
    char dest[40];
} ManifestStep;

typedef struct {
    FILE *manifest_fp;
    int num_steps;
    int cur_step_idx;
    char base_path[MAX_MANIFEST_PATH_LEN];
    char cur_step_cmd[MAX_MANIFEST_STEP_LEN];
    ManifestStep ms;
} Manifest;

/**
 * Loads and initializes a manifest file
 * 
 * @param manifest_file The file to load
 * @param m a pointer to a Manifest
 * @return 0 if the file was loaded sucessfully, non-zero otherwise
 * 
 * @note This will create a list of ManifestSteps.  It will need to be freed afterward
*/
int load_manifest(char *manifest_file, Manifest *m);

/** 
 * Unloads a manifest file structure and frees memory
 * 
 * @param m A pointer to the manifest to clean
 * @return 0 if sucessful, non-zero otherwise
 */
int unload_manifest(Manifest *m);

/**
 * Reads the next manifest step from the file and stores it
 * 
 * @param m A pointer to the manifest to process
 * @return 0 if completed sucessfully, non-zero otherwise
*/
int get_manifest_step(Manifest *m);

/**
 * Performs the next step of the manifest file
 * 
 * @param m A pointer to the manifest to process
 * @return 0 if the step completed sucessfully, non-zero otherwise 
 */
int perform_manifest_step(Manifest *m);

/**
 * Gets the total number of steps in the manifest
 * 
 * @param m A pointer to the manifest to query
 * @return int The number of steps in the manifest, or -1 if there was an issue
 */
int get_num_manifest_steps(Manifest *m);

/**
 * Gets the current step of the manifest
 * 
 * @param m A pointer to the manifest to query
 * @return The current step in the manifest, or -1 if there was an issue
 */
int get_cur_manifest_step(Manifest *m);

/** 
 * Gets the string of the current manifest command
 * 
 * @param m A pointer to the manifest to query
 * @return a pointer to the command string
 */
char *get_cur_manifest_step_cmd(Manifest *m);

/**
 * Returns if the manifest file has no steps left
 * 
 * @param m A pointer to the manifest to query
 * @return 1 if complete, 0 if not
 */
int manifest_complete(Manifest *m);

/**
 * Sets the base path for manifest operations
 * 
 * @param m A pointer to the manifest to update
 * @param path The base path to use
 * @return Nothing
*/
void set_manifest_base_path(Manifest *m, char *path);

extern Manifest g_manifest;

#endif
