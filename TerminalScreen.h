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
    ~TerminalScreen();
    void addWindow(TerminalWindow* window);
    void popWindow();
    TerminalWindow* getTopWindow();
    void redrawScreen();
    void loop();
  private:
    BasicTerm* term = NULL;
    TerminalWindow* windows[WINDOW_MAX_COUNT];
    int windowindex = -1;
    bool needRedraw = false;
    unsigned long lastRedraw = 0;
    void draw();
    String title = "";
    uint16_t key = 0;
};

#endif
