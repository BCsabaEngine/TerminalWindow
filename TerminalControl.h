/*
  TerminalWindow.h - Library for make screen and windows for VT220 screens
  Created by Csaba Balazs, March 22, 2021
  Released into the public domain.
*/

#ifndef TerminalControl_h
#define TerminalControl_h

#include <BasicTerm.h>

class TerminalControl
{
  public:
    TerminalControl(int x, int y, int width);
    virtual void draw(BasicTerm* term);
  protected:
    int x;
    int y;
    int width;
};

enum HAlign {
  left,
  center,
  right,
};

class TerminalLabel: public TerminalControl
{
  public:
    TerminalLabel(int x, int y, int width, const char* text, HAlign halign = left);
    virtual void draw(BasicTerm* term);
  protected:
    const char* text;
    HAlign halign;
};

/*
  class TerminalButton: public TerminalControl
  {
  public:
    TerminalButton(int x, int y, char* text);
    virtual void Draw();
  };
*/
#endif
