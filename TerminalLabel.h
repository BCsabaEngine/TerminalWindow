#ifndef TerminalLabel_h
#define TerminalLabel_h

#include <BasicTerm.h>
#include "TerminalControl.h"

class TerminalLabel: public TerminalControl
{
  public:
    TerminalLabel(int x, int y, int width, String text, HAlign halign = left);
    void setText(String text);
    virtual void draw(BasicTerm* term, bool focused);
  private:
    String text = "";
    HAlign halign = left;
};

#endif
