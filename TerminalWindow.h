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
    void init();
    TerminalScreen* getScreen();
    void setScreen(TerminalScreen* screen);
    void addControl(TerminalControl* control);
    void processKey(uint16_t key);
  private:
    TerminalScreen* screen = NULL;
    TerminalControl* controls[CONTROL_MAX_COUNT];
    int controlcount = 0;
    TerminalControl* focused = NULL;
    void prevFocus();
    void nextFocus();
};

#endif
