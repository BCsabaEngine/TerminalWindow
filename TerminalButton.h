#ifndef TerminalButton_h
#define TerminalButton_h

#include <BasicTerm.h>
#include "TerminalControl.h"

class TerminalButton: public TerminalControl
{
  public:
    TerminalButton(int x, int y, int width, const char* text, HAlign halign = center);
    virtual void draw(BasicTerm* term, bool focused);
    virtual bool canFocus() {
      return true;
    }
  private:
    char* text;
    HAlign halign;
};

#endif
