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
#ifndef __DAMPBN_H__
#define __DAMPBN_H__

/**
 * States for the state machine!
*/
typedef enum {
  STATE_NONE,
  STATE_LOGO,
  STATE_TITLE,
  STATE_GAME,
  STATE_LOAD,
  STATE_SAVE,
  STATE_HELP,
  STATE_OPTS,
  STATE_MAP,
  STATE_LOAD_DIALOG,
  STATE_FINISHED,
  STATE_REPLAY
} State;

/* Definitions from dpmi.h */
unsigned long _go32_dpmi_remaining_physical_memory(void);
unsigned long _go32_dpmi_remaining_virtual_memory(void);

/**
 * Change the current state of the state machine
 * 
 * @param new_state the state to change to
 * @param prev_state the state we're currently in
 * 
 * @note prev_state is used to ensure that certain things happen in state
 *       transitions that are dependent on the particular state that the game
 *       was in.  For example, the load dialog screen animates the background
 *       when shown on the title screen, but not when shown in game.
 */
void change_state(State new_state, State prev_state);

/**
 * Turns the game timer (for elapsed time) on or off.
 * 
 * @param status 0 to stop the timer, non-zero to start it
 */
void game_timer_set(int status);

/**
 * Updates the display.
 * 
 * @note by default, runs once a frame.  It can be called at any time to 
 *       force an update.  This is used by dialogs that are only shown 
 *       transiently or as part of a state change.
 */
void do_render(void);

/**
 * Decrement counters and do things when they expire
 */
void process_timing_stuff(void);

/**
 * Show free DPMI memory (physical + virtual)
 * 
 * @note this is a debug function and isn't used in final code.
 */
void print_mem_free(void);

#endif
