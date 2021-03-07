#ifndef TerminalScreen_h
#define TerminalScreen_h

#include <BasicTerm.h>
#include <MemoryFree.h>
#include "TerminalConfig.h"
#include "TerminalWindow.h"

class TerminalWindow;
class TerminalScreen
{
  public:
    TerminalScreen(char* title);
    void addWindow(TerminalWindow* window);
    void popWindow();
    TerminalWindow* getTopWindow();
    void draw();
    void loop();
  private:
    BasicTerm* term;
    TerminalWindow* windows[WINDOW_MAX_COUNT];
    int windowindex = -1;
    char* title;
};

#endif
