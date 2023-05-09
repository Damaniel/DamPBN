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
#include "../include/audio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dir.h>

char g_midi_files[MAX_MIDIS][80];
MIDI *g_active_midi;

int g_cur_midi_idx;
int g_total_midis;


int initialize_audio_subsystem(void) {
    int result;

    result = detect_digi_driver(DIGI_AUTODETECT);
    if (result == 0) {
        printf("Sound card not detected!\n");
        return -1;
    } else {
        printf("Sound card detected - %d voices available\n", result);
    }

    result = detect_midi_driver(MIDI_AUTODETECT);
    if (result == 0) {
        printf("MIDI device not detected!\n");
        return -1;
    } else {
        printf("MIDI card detected - %d voices available\n", result);
    }

    result = install_sound(DIGI_NONE, MIDI_AUTODETECT, NULL);
    if (result == -1) {
        printf("Unable to initialize sound system!\n");
        printf("Error was %s\n", allegro_error);
        return -1;
    }
    return 0;
}

void shut_down_audio_subsystem(void) {
    // Nothing needs to be done here
}

int load_midis_from_default_dir(void)
{
    int result;
    
    result = load_midis_from_dir(DEFAULT_MIDI_DIRECTORY);
    return result;
}

int load_midis_from_dir(char *directory) {
    struct ffblk f;
    int done;
    int total_files;
    char mid_pathspec[64];
    char mid_filename[80];
    char *filename;

    sprintf(mid_pathspec, "%s/*.mid", directory);

    /* Reset file count.  There may be extra files from a previous call in
       the structure, but if the total file count is correct, we don't 
       really care. */
    total_files = 0;
    g_total_midis = 0;
    done = findfirst(mid_pathspec, &f, 0);
    while (!done && total_files < MAX_MIDIS) 
    {
        filename = strtok(f.ff_name, ".");
        sprintf(mid_filename, "%s/%s.mid", directory, filename);
        strncpy(g_midi_files[g_total_midis], mid_filename, 80);
        g_total_midis++;
        total_files++;
        done = findnext(&f);
    } 
    return g_total_midis;
}

int play_cur_midi(int play_next_after) {
    printf("Playing %s\n", g_midi_files[g_cur_midi_idx]);
    g_active_midi = load_midi(g_midi_files[g_cur_midi_idx]);
    if(g_active_midi == NULL) {
        printf("Couldn't load MIDI!\n");
        return -1;
    }
    play_midi(g_active_midi, 0);
    return 0;
}

int play_midi_by_idx(int idx) {
    if (idx >= g_total_midis) {
        printf("MIDI index invalid!\n");
        return -1;
    }
    printf("Playing %s\n", g_midi_files[idx]);
    g_active_midi = load_midi(g_midi_files[idx]);
    if(g_active_midi == NULL) {
        printf("Couldn't load MIDI!\n");
        return -1;
    }
    play_midi(g_active_midi, 0);    
    return 0;
}

int cue_next_midi(int play_next_after) {
    g_cur_midi_idx = (g_cur_midi_idx + 1) % g_total_midis;
    play_cur_midi(1);
}

int is_midi_done(void) {
    if (midi_pos < 0) {
        return 1;
    }
    return 0;
}

int play_midi_by_name(char *name) {
    g_active_midi = load_midi(name);
    if(g_active_midi == NULL) {
        printf("Couldn't load MIDI!\n");
        return -1;
    }
    play_midi(g_active_midi, 0);
    return 0;
}

int pause_active_midi(void) {
    midi_pause();
    return 0;
}

int resume_active_midi(void) {
    midi_resume();
    return 0;
}

int stop_active_midi(void) {
    stop_midi();
    return 0;
}
