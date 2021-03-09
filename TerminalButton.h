#ifndef TerminalButton_h
#define TerminalButton_h

#include <BasicTerm.h>
#include "TerminalControl.h"

class TerminalButton;
typedef void (*buttonFuncPtr)(TerminalButton *button);
class TerminalButton: public TerminalControl
{
  private:
    String text;
    buttonFuncPtr clickhandler = NULL;
  public:
    TerminalButton(byte x, byte y, byte width, String text);
    void setText(String text);
    virtual void draw(BasicTerm* term, bool focused);
    virtual bool canFocus() {
      return true;
    }
    virtual bool handleKey(uint16_t key);
    void setClickHandler(buttonFuncPtr clickhandler) {
      this->clickhandler = clickhandler;
    }
};

#endif
