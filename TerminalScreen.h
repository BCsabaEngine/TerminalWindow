/*
  TerminalWindow.h - Library for make screen and windows for VT220 screens
  Created by Csaba Balazs, March 22, 2021
  Released into the public domain.
*/

#ifndef TerminalScreen_h
#define TerminalScreen_h

#include <BasicTerm.h>
#include "TerminalWindow.h"

#define WINDOW_MAX_COUNT 10

class TerminalWindow;
class TerminalScreen
{
  public:
    TerminalScreen();
    void addWindow(TerminalWindow* window);
    void popWindow();
    TerminalWindow* getTopWindow();
    void draw();
    void loop();
  private:
    BasicTerm* term;
    TerminalWindow* _windows[WINDOW_MAX_COUNT];
    int _windowindex = -1;
};

#endif
