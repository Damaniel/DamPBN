#ifndef __INSTALL_H__
#define __INSTALL_H__

#include "textdraw.h"
#include "input.h"
#include "render.h"
#include "util.h"
#include "manifest.h"
#include <stdio.h>
#include <bios.h>
#include <dos.h>
#include <string.h>

// Keyboard scancodes
#define KEY_ESC                 0x01
#define KEY_UP                  0x48
#define KEY_DOWN                0x50
#define KEY_LEFT                0x4B
#define KEY_RIGHT               0x4D
#define KEY_LBRACKET            0x1A
#define KEY_RBRACKET            0x1B
#define KEY_SPACE               0x39
#define KEY_BACKSLASH           0x2B
#define KEY_ENTER               0x1C
#define KEY_BACKSPACE           0x0E
#define KEY_EQUALS              0x0D
#define KEY_A                   0x1E
#define KEY_B                   0x30
#define KEY_C                   0x2E
#define KEY_D                   0x20
#define KEY_E                   0x12
#define KEY_F                   0x21
#define KEY_G                   0x22
#define KEY_H                   0x23
#define KEY_I                   0x17
#define KEY_J                   0x24
#define KEY_K                   0x25
#define KEY_L                   0x26
#define KEY_M                   0x32
#define KEY_N                   0x31
#define KEY_O                   0x18
#define KEY_P                   0x19
#define KEY_Q                   0x10
#define KEY_R                   0x13
#define KEY_S                   0x1F
#define KEY_T                   0x14
#define KEY_U                   0x16
#define KEY_V                   0x2F
#define KEY_W                   0x11
#define KEY_X                   0x2D
#define KEY_Y                   0x15
#define KEY_Z                   0x2C
#define KEY_0                   0x0B
#define KEY_1                   0x02
#define KEY_2                   0x03
#define KEY_3                   0x04
#define KEY_4                   0x05
#define KEY_5                   0x06
#define KEY_6                   0x07
#define KEY_7                   0x08
#define KEY_8                   0x09
#define KEY_9                   0x0A
#define KEY_DELETE              0x53

#define MAX_PATH_LENGTH     64
#define DEFAULT_PATH "C:\\DamPBN\\"
#define REQUIRED_MB         3

typedef enum {
    STATE_MAIN_SCREEN,
    STATE_INVALID_PATH_SCREEN,
    STATE_CONFIRM_EXISTING_SCREEN,
    STATE_COPY_SCREEN,
    STATE_COMPLETE_SCREEN
} State;

extern State g_cur_state;
extern State g_prev_state;
extern int g_exit;
extern RenderComponents g_render_components;
extern char g_install_path[MAX_PATH_LENGTH];
extern int g_edit_cursor_x, g_edit_cursor_y, g_old_edit_cursor_x, g_edit_display_offset;

extern void set_state(State s);

#endif
