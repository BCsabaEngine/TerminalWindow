#ifndef TerminalConfig_h
#define TerminalConfig_h

#define SCREEN_HEADER_LINES 2
#define SCREEN_REDRAW_LATENCY_MS 100
#define SCREEN_REDRAW_MAX_LATENCY_MS 5 * 1000
#define WINDOW_ROUTE_LINES 2
#define WINDOW_MAX_DEPTH 6
#define CONTROL_MAX_COUNT 24
#define AUTO_MAINWINDOW_SEC 5 * 60

#define WINDOW_CLOSE_ESC
#define CONTROL_MOVE_UP_DOWN
//#define CONTROL_MOVE_LEFT_RIGHT
#define CONTROL_MOVE_TAB

#define CONTROL_BUTTON_SPACE
#define CONTROL_BUTTON_ENTER
#define CONTROL_BUTTON_DECORATOR

#define CONTROL_CHECKBOX_SPACE
#define CONTROL_CHECKBOX_ENTER
//#define CONTROL_CHECKBOX_UP_DOWN
#define CONTROL_CHECKBOX_LEFT_RIGHT
#define CONTROL_CHECKBOX_DECORATOR

#define CONTROL_SELECT_SPACE
#define CONTROL_SELECT_ENTER
//#define CONTROL_SELECT_UP_DOWN
#define CONTROL_SELECT_LEFT_RIGHT
#define CONTROL_SELECT_MAX_ITEMCOUNT 8
//#define CONTROL_SELECT_DECORATOR

#define CONTROL_NUM_SPACE
#define CONTROL_NUM_ENTER
//#define CONTROL_NUM_UP_DOWN
#define CONTROL_NUM_LEFT_RIGHT
#define CONTROL_NUM_MAXLATENCY_MS 750
//#define CONTROL_NUM_ALIGN_RIGHT
//#define CONTROL_NUM_DECORATOR

//#define CONTROL_TEXT_DECORATOR

#endif
