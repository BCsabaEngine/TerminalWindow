#ifndef TerminalScreen_h
#define TerminalScreen_h

#include "lib/BasicTerm.h"
#include "TerminalConfig.h"
#include "TerminalWindow.h"

class TerminalWindow;
typedef void (*screenDisplayDebugInfoFuncPtr)(String &debuginfo);
class TerminalScreen
{
private:
  BasicTerm *term = NULL;
  TerminalWindow *windows[WINDOW_MAX_DEPTH];
  int windowindex = -1;
  uint8_t borderWidth = 0;
  uint8_t borderHeight = 0;
  bool borderVertical = false;
  bool needRedraw = false;
  unsigned long lastRedraw = 0;
  unsigned long lastKeyPress = 0;
  void draw();
  String title = "";
  String footer = "";
  int16_t key = 0;
  bool debug = false;
  bool hasBorder() { return this->borderWidth > 0 && this->borderHeight > 0; }
  screenDisplayDebugInfoFuncPtr displaydebuginfo = NULL;

public:
  TerminalScreen(String title, String footer = "");
  ~TerminalScreen();
  void setDebug(bool debug, screenDisplayDebugInfoFuncPtr displaydebuginfo = NULL)
  {
    this->debug = debug;
    if (debug)
      this->displaydebuginfo = displaydebuginfo;
    else
      this->displaydebuginfo = NULL;
  }
  void setBorder(uint8_t width, uint8_t height, bool showvertical = false)
  {
    this->borderWidth = width;
    this->borderHeight = height;
    this->borderVertical = showvertical;
  }
  void resetBorder() { this->borderWidth = this->borderHeight = 0; }
  void setTitle(String title) { this->title = title; }
  void setFooter(String footer) { this->footer = footer; }
  void addWindow(TerminalWindow *window);
  void popWindow();
  TerminalWindow *getTopWindow();
  void redrawScreen();
  void loop();
};

#endif
