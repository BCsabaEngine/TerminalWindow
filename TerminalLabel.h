#ifndef TerminalLabel_h
#define TerminalLabel_h

#include <BasicTerm.h>
#include "TerminalControl.h"

class TerminalLabel: public TerminalControl
{
  public:
    TerminalLabel(int x, int y, int width, const char* text, HAlign halign = left);
    virtual void draw(BasicTerm* term, bool focused);
  private:
    char* text = NULL;
    HAlign halign = left;
};

#endif
