#ifndef TerminalScreen_h
#define TerminalScreen_h

#include <BasicTerm.h>
#include "TerminalConfig.h"
#include "TerminalWindow.h"

class TerminalWindow;
class TerminalScreen
{
  public:
    TerminalScreen(String title);
    void addWindow(TerminalWindow* window);
    void popWindow();
    TerminalWindow* getTopWindow();
    void draw();
    void loop();
  private:
    BasicTerm* term = NULL;
    TerminalWindow* windows[WINDOW_MAX_COUNT];
    int windowindex = -1;
    String title = "";
    uint16_t key = 0;
};

#endif
