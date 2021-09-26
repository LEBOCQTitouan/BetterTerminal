/**
 * sources : 
 * - https://www.theurbanpenguin.com/4184-2/
 * - https://en.wikipedia.org/wiki/ANSI_escape_code
 * - https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
 */
#ifndef BETTER_TERMINAL_H
#define BETTER_TERMINAL_H

// standard import
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
// custom import
// NONE

// const
#define ESCAPE_SEQUENCE "\033"

// defining types

typedef enum colors {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    PURPLE,
    CYAN,
    WHITE,
    DEFAULT_COLOR
} color;

typedef enum styles {
    BOLD,
    ITALIC,
    UNDERLINE,
    DEFAULT_STYLE
} style;

typedef enum directions {
    CURSOR_UP,
    CURSOR_DOWN,
    CURSOR_RIGHT,
    CURSOR_LEFT
} direction;

/**
 * The getANSIColorValue() function will return the ANSI escape code value of the given color.
 * 
 * @param color the color from which we want the ANSI value
 * 
 * @return the ANSI escape code (str) of the given color
 */
char * getANSIColorValue(color color);

/**
 * The getANSIColorValue() function will return the ANSI escape code value of the given color.
 * 
 * @param color the color from which we want the ANSI value
 * 
 * @return the ANSI escape code (str) of the given color
 */
char * getANSIBgColorValue(color color);

/**
 * The getANSIStyleValue() function will return the ANSI escape code value of the given style.
 * 
 * @param style the style from which we want the ANSI value
 * 
 * @return the ANSI escape code (str) of the given style
 */
char * getANSIStyleValue(style style);

/**
 * The printfColored() function will have the exact same comportement as printf but will display
 * the given string with the given color.
 * 
 * @param color the color in which print the str
 * @param format the str which will be printed (support same escape code as printf)
 * 
 * @return the return value of the vprintf
 */
int printfColored(color fontColor, color bgColor, style style, const char * format, ...);

/**
 * The clearTerminal() function clear the terminal using the native os command (on both windows and unix).
 */
void clearTerminal();

/**
 * The eraseAllTerminal() function erase all char from the terminal.
 */
void clearAllTerminal();

/**
 * The moveCursor() function will move the terminal cursor to the given line and column.
 */
void moveCursor(int line, int column);

/**
 * The getANSIDirectionValue() will return the ANSI escape code corresponding to the direction
 */
char * getANSIDirectionValue(direction direction);

/**
 * The moveCursorRelative() function will move the cursor relatively to it's current location.
 * 
 * @param direction the direction in which you want to move yout cursor
 * @param iterationNumber the number of time you want to move the cursor
 */
void moveCursorRelative(direction direction, int iterationNumber);

/**
 * The moveCursorToBeginningRelative() function will move the cursor up or down n lines and position it
 * on the start of the line.
 * 
 * @param lines the number of line you want to move down (negative => upward)
 */
void moveCursorOnStartRelative(int lines);

/**
 * The home() function will move the cursor to the position [0, 0]
 */
void home();

/**
 * The clearFromCursor() function will delete all char from the current cursor postion to end of screen.
 * 
 * @param direction the direction in which you want to erase the terminal (only CURSOR_UP and CURSOR_DOWN)
 */
void clearFromCursor(direction direction);

/**
 * The clearLine() function will errase the current line in the choosen direction (if no direction given erase all the line).
 * 
 * @param direction the direction in which you want to erase the line (only CURSOR_LEFT and CURSOR_RIGHT)
 */
void clearLine(direction direction);

#endif // BETTER_TERMINAL_H