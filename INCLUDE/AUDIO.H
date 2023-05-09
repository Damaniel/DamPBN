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
#ifndef __AUDIO_H__
#define __AUDIO_H__
#include <allegro.h>

#define MAX_MIDIS   16

#define DEFAULT_MIDI_DIRECTORY      "res/music"
#define TITLE_MUSIC                 "res/APPMIDI/title.mid"
#define COMPLETE_MUSIC              "res/APPMIDI/complete.mid"

extern char g_midi_files[MAX_MIDIS][80];
extern MIDI *g_active_midi;

extern int g_cur_midi_idx;
extern int g_total_midis;

/**
 * Initializes the audio system
 * 
 * @return 0 if the system was sucessfully started, non-zero otherwise
 */
int initialize_audio_subsystem(void);

/**
 * Shuts down the audio system 
 */
void shut_down_audio_subsystem(void);

/**
 * Populates the g_midi_files structure with the first MAX_MIDIS MIDI files in 
 * the default directory
 * 
 * @return The number of MIDIs loaded, or -1 if there was an error
 */
int load_midis_from_default_dir(void);

/**
 * Populates the g_midi_files structure with the first MAX_MIDIS MIDI files in
 * the specified directory
 * 
 * @param directory The directory to read MIDI files from
 * @return The number of MIDIs loaded, or -1 if there was an error
 */
int load_midis_from_dir(char *directory);

/**
 * Plays the MIDI file defined by g_midi_files[g_cur_midi]
 * 
 * @param play_next_after Should the next MIDI in the list be played after this one?
 *                        (0 = repeat this MIDI again, 1 = play the next one)
 * @return 0 on success, non-zero on failure
 */
int play_cur_midi(int play_next_after);

/**
 * Plays the MIDI file defined by g_midi_files[idx]
 * 
 * @param idx The index of the MIDI file to play
 * @return 0 on success, non-zero on failure
 */
int play_midi_by_idx(int idx);

/**
 * Plays the MIDI file specified by file name
 * 
 * @param name The file name (including path) of the MIDI file to play
 * @return 0 on success, non-zero on failure
 */
int play_midi_by_name(char *name, int loop);

/**
 * Stops the (playing) active MIDI file
 * 
 * @return 0 on success, non-zero otherwise
 * @note This function won't likely return a value other than zero, as the only
 *       function within it returns void.
 */
int stop_active_midi(void);

/**
 * Pauses playback of the (playing) active MIDI file
 * 
 * @return 0 on success, non-zero otherwise
 * @note This function won't likely return a value other than zero, as the only
 *       function within it returns void.
 */
int pause_active_midi(void);

/**
 * Resumes playback of the (paused) active MIDI file
 * 
 * @return 0 on success, non-zero otherwise
 * @note This function won't likely return a value other than zero, as the only
 *       function within it returns void.
 */
int resume_active_midi(void);

/**
 * Checks if the active MIDI is finished playing
 * 
 * @return 1 if the MIDI is finished, 0 otherwise.
 */
int is_midi_done(void);

int cue_next_midi(int play_next_after);

void mute_music(void);

void mute_sound(void);

void restore_sound(void);
void restore_music(void);

#endif