// header file
#include "betterTerminal.h"
// end header file

bool needReset = false;

char * getANSIColorValue(color color) {
    switch (color)
    {
    case BLACK:         return "30";
    case RED:           return "31";
    case GREEN:         return "32";
    case YELLOW:        return "33";
    case BLUE:          return "34";
    case PURPLE:        return "35";
    case CYAN:          return "36";
    case WHITE:         return "37";
    case DEFAULT_COLOR: return "39";
    default:            return NULL; // ERROR
    }
}

char * getANSIBgColorValue(color color) {
    switch (color)
    {
    case BLACK:         return "40";
    case RED:           return "41";
    case GREEN:         return "42";
    case YELLOW:        return "43";
    case BLUE:          return "44";
    case PURPLE:        return "45";
    case CYAN:          return "46";
    case WHITE:         return "47";
    case DEFAULT_COLOR: return "49";
    default:            return NULL; // ERROR
    }
}

char * getANSIStyleValue(style style) {
    switch (style)
    {
    case DEFAULT_STYLE: return "0";
    case BOLD:          return "1";
    case ITALIC:        return "3";
    case UNDERLINE:     return "4";
    default: break;
    }
}

int printfColored(color fontColor, color bgColor, style style, const char * format, ...) {
    va_list argList;
    int returnValue;
    char * ansiFontColorStr = getANSIColorValue(fontColor),
         * ansiBgColorStr   = getANSIBgColorValue(bgColor),
         * ansiStyle        = getANSIStyleValue(style);

    if (ansiFontColorStr == NULL || ansiBgColorStr == NULL) { return -1; } // ERROR in the colors
    printf("\033[%s;%s;%sm", ansiStyle, ansiFontColorStr, ansiBgColorStr); // setting the color

    va_start(argList, format);
    returnValue = vprintf(format, argList);
    va_end(argList);

    printf("\033[0m"); // reset of the color
    return returnValue;
}

void clearTerminal() {
    // UNIX clear
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    // WINDOWS clear
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

void moveCursor(int line, int column) {
    printf("\033[%d;%dH", line, column);
}

char * getANSIDirectionValue(direction direction) {
    switch (direction)
    {
    case CURSOR_DOWN:       return "B";
    case CURSOR_LEFT:       return "D";
    case CURSOR_RIGHT:      return "C";
    case CURSOR_UP:         return "A";
    default:                return NULL; // ERROR
    }
}

void moveCursorRelative(direction direction, int iterationNumber) {
    char * ANSIDirectionStr = getANSIDirectionValue(direction);
    if (ANSIDirectionStr != NULL) printf("\033[%d%s", iterationNumber, ANSIDirectionStr);
}

void clearAllTerminal() {
    printf("\033[2J");
}

void moveCursorOnStartRelative(int lines) {
    if (lines < 0) { // up
        printf("\033[%dF", lines);
    } else { // down
        printf("\033[%dE", lines);
    }
}

void home() {
    printf("\033[H");
}

void clearFromCursor(direction direction) {
    switch (direction)
    {
    case CURSOR_UP:
        printf("\033[1J");
        break;
    case CURSOR_DOWN:
        printf("\033[0J");
        break;
    default: break;
    }
}

void clearLine(direction direction) {
    switch (direction)
    {
    case CURSOR_LEFT:
        printf("\033[1K");
    case CURSOR_RIGHT:
        printf("\033[0K");
        break;
    default: break;
    }
}

void makeCursorVisible() {
    printf("\033[?25h");
    needReset = false;
}

void makeCursorInvisible() {
    printf("\033[?25l");
    if (!needReset) {
        atexit(&makeCursorVisible);
        needReset = true;
    }
}

int printfColoredRGB(int fontR, int fontG, int fontB, int backgroundR, int backgroundG, int backgroundB, const char * format, ...){
    va_list argList;
    int returnValue;

    // char * ansiFontColorStr = getANSIColorValue(fontColor),
    //      * ansiBgColorStr   = getANSIBgColorValue(bgColor),
    // char * ansiStyle = getANSIStyleValue(style);

    // if (ansiFontColorStr == NULL || ansiBgColorStr == NULL) { return -1; } // ERROR in the colors
    // printf("\033[%s;%s;%sm", ansiStyle, ansiFontColorStr, ansiBgColorStr); // setting the color

    printf("\033[38;2;%d;%d;%dm", fontR, fontG, fontB);
    printf("\033[48;2;%d;%d;%dm", backgroundR, backgroundG, backgroundB);
    // printf("\033[%sm", getANSIStyleValue);

    va_start(argList, format);
    returnValue = vprintf(format, argList);
    va_end(argList);

    printf("\033[0m"); // reset of the color
    return returnValue;
}