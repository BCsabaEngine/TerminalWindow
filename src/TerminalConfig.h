#ifndef TerminalConfig_h
#define TerminalConfig_h

#define SCREEN_HEADER_LINES 2
#define SCREEN_REDRAW_LATENCY_MS 100
#define SCREEN_REDRAW_MAX_LATENCY_MS 5 * 1000
#define WINDOW_ROUTE_LINES 2
#define WINDOW_MAX_COUNT 10
#define CONTROL_MAX_COUNT 16
#define CONTROL_EDIT_MAXLATENCY_MS 750
#define CONTROL_SELECT_MAX_ITEMCOUNT 8
#define AUTO_MAINWINDOW_SEC 5 * 60

#define WINDOW_CLOSE_ESC
#define CONTROL_MOVE_UP_DOWN
//#define CONTROL_MOVE_LEFT_RIGHT
#define CONTROL_MOVE_TAB
#define CONTROL_BUTTON_SPACE
#define CONTROL_BUTTON_ENTER
#define CONTROL_CHECKBOX_SPACE
#define CONTROL_CHECKBOX_ENTER
//#define CONTROL_CHECKBOX_UP_DOWN
#define CONTROL_CHECKBOX_LEFT_RIGHT
//#define CONTROL_EDIT_UP_DOWN
#define CONTROL_EDIT_LEFT_RIGHT

#endif
