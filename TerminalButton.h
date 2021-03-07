#ifndef TerminalButton_h
#define TerminalButton_h

#include <BasicTerm.h>
#include "TerminalControl.h"

class TerminalButton;
typedef void (*buttonFuncPtr)(TerminalButton *button);
class TerminalButton: public TerminalControl
{
  public:
    TerminalButton(int x, int y, int width, const char* text);
    virtual void draw(BasicTerm* term, bool focused);
    virtual bool canFocus() {
      return true;
    }
    virtual bool handleKey(uint16_t key);
    void setClickHandler(volatile buttonFuncPtr clickhandler) {
      this->clickhandler = clickhandler;
    }
    void SetText(const char* text) {
      this->text = (char*)text;
    }
  private:
    char* text = NULL;
    buttonFuncPtr clickhandler = NULL;
};

#endif
