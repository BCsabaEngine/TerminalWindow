#ifndef TerminalCheckbox_h
#define TerminalCheckbox_h

#include <BasicTerm.h>
#include "TerminalControl.h"

class TerminalCheckbox;
typedef void (*checkboxFuncPtr)(TerminalCheckbox *checkbox, bool value);
class TerminalCheckbox: public TerminalControl {
  private:
    bool value = false;
    String offtext;
    String ontext;
    checkboxFuncPtr changehandler = NULL;
  public:
    TerminalCheckbox(byte x, byte y, byte width, String ontext = "x", String offtext = " ");
    bool getValue();
    void setValue(bool value);
    virtual void draw(BasicTerm* term, bool focused);
    virtual bool canFocus() {
      return true;
    }
    virtual bool handleKey(uint16_t key);
    void setChangeHandler(checkboxFuncPtr changehandler) {
      this->changehandler = changehandler;
    }
};

#endif
