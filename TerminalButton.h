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
    virtual bool handleKey(uint16_t key);
  private:
    char* text = NULL;
    HAlign halign = center;
};

#endif
