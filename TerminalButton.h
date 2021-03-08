#ifndef TerminalButton_h
#define TerminalButton_h

#include <BasicTerm.h>
#include "TerminalControl.h"

class TerminalButton;
typedef void (*buttonFuncPtr)(TerminalButton *button);
class TerminalButton: public TerminalControl
{
  public:
    TerminalButton(int x, int y, int width, String text);
    void setText(String text);
    virtual void draw(BasicTerm* term, bool focused);
    virtual bool canFocus() {
      return true;
    }
    virtual bool handleKey(uint16_t key);
    void setClickHandler(volatile buttonFuncPtr clickhandler) {
      this->clickhandler = clickhandler;
    }
  private:
    String text = "";
    buttonFuncPtr clickhandler = NULL;
};

#endif
