#ifndef __ESCAPE_SEQ_H
#define __ESCAPE_SEQ_H

#include <detpic32.h>

// Attributes
#define RESETATTR    0x00
#define BRIGHT       0x01
#define DIM          0x02
#define UNDERSCORE   0x04
#define BLINK        0x05
#define REVERSE      0x07

// Colors
#define BLACK        0x00
#define RED          0x01
#define GREEN        0x02
#define BROWN        0x03
#define BLUE         0x04
#define MAGENTA      0x05
#define CYAN         0x06
#define LIGHTGREY    0x07

#define DARKGREY     0x10
#define LIGHTRED     0x11
#define LIGHTGREEN   0x12
#define YELLOW       0x13
#define LIGHTBLUE    0x14
#define LIGHTMAGENTA 0x15
#define LIGHTCYAN    0x16
#define WHITE        0x17

// ESC sequences

// Esc[2JEsc[1;1H    : Clear screen and move cursor to (1,1) (x=1, y=1, i.e., upper left position)
#define clrscr()     printStr("\e[2J\e[1;1H")

// Esc[K             : Erase from the current cursor position to the end of the current line
#define erase2eol()  printStr("\e[K")

// Esc[2K            : Erase the entire current line
#define eraseline()  printStr("\e[2K")

// Esc[Line;ColumnH  : Move the cursor to the specified position
#define gotoxy(x,y)  printf("\e[%d;%dH", y, x)

// Esc[?25l (lower case L)  : Hide Cursor
#define hidecursor() printStr("\e[?25l")

// Esc[?25h (lower case H)  : Show Cursor
#define showcursor() printStr("\e[?25h")

// Esc[Value;...;Valuem     : Set Graphics Mode
#define textattr(attr)        printf("\e[%dm", attr)
#define textcolor(color)      printf("\e[%d;%dm", color & 0x10 ? 1 : 0, (color & 0x0F) + 30)
#define textbackground(color) printf("\e[%d;%dm", color & 0x10 ? 1 : 0, (color & 0x0F) + 40)

#endif

