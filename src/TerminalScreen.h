#ifndef TerminalScreen_h
#define TerminalScreen_h

#include "lib/BasicTerm.h"
#include "TerminalConfig.h"
#include "TerminalWindow.h"

class TerminalWindow;
class TerminalScreen
{
private:
  BasicTerm *term = NULL;
  TerminalWindow *windows[WINDOW_MAX_DEPTH];
  int windowindex = -1;
  uint8_t borderWidth = 0;
  uint8_t borderHeight = 0;
  bool needRedraw = false;
  unsigned long lastRedraw = 0;
  unsigned long lastKeyPress = 0;
  void draw();
  String title = "";
  int16_t key = 0;
  bool debug = false;
  bool hasBorder() { return this->borderWidth && this->borderHeight; }

public:
  TerminalScreen(String title, bool debug = false);
  ~TerminalScreen();
  void setBorder(uint8_t width, uint8_t height)
  {
    this->borderWidth = width;
    this->borderHeight = height;
  }
  void resetBorder() { this->borderWidth = this->borderHeight = 0; }
  void addWindow(TerminalWindow *window);
  void popWindow();
  TerminalWindow *getTopWindow();
  void redrawScreen();
  void loop();
};

#endif
