/*
  TerminalWindow.h - Library for make screen and windows for VT220 screens
  Created by Csaba Balazs, March 22, 2021
  Released into the public domain.
*/

#ifndef TerminalWindow_h
#define TerminalWindow_h

#include <BasicTerm.h>
#include "TerminalScreen.h"
#include "TerminalControl.h"

#define CONTROL_MAX_COUNT 32

class TerminalScreen;
class TerminalControl;
class TerminalWindow
{
  public:
    TerminalWindow();
    void draw(BasicTerm* term);
    void close();
    void setScreen(TerminalScreen* screen);
    void addControl(TerminalControl* control);
  private:
    TerminalScreen* _screen;
    TerminalControl* _controls[CONTROL_MAX_COUNT];
    int _controlcount = 0;
};

#endif
