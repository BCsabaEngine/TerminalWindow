#ifndef TerminalWindow_h
#define TerminalWindow_h

#include <BasicTerm.h>
#include "TerminalConfig.h"
#include "TerminalScreen.h"
#include "TerminalControl.h"

class TerminalScreen;
class TerminalControl;
class TerminalWindow
{
  public:
    TerminalWindow();
    void draw(BasicTerm* term);
    void close();
    TerminalScreen* getScreen();
    void setScreen(TerminalScreen* screen);
    void addControl(TerminalControl* control);
  private:
    TerminalScreen* screen;
    TerminalControl* controls[CONTROL_MAX_COUNT];
    int controlcount = 0;
};

#endif
