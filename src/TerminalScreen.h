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
  TerminalWindow *windows[WINDOW_MAX_COUNT];
  int windowindex = -1;
  bool needRedraw = false;
  unsigned long lastRedraw = 0;
  unsigned long lastKeyPress = 0;
  void draw();
  String title = "";
  int16_t key = 0;
  bool debug = false;

public:
  TerminalScreen(String title, bool debug = false);
  ~TerminalScreen();
  void addWindow(TerminalWindow *window);
  void popWindow();
  TerminalWindow *getTopWindow();
  void redrawScreen();
  void loop();
};

#endif
