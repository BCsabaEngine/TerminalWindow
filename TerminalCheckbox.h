#ifndef TerminalCheckbox_h
#define TerminalCheckbox_h

#include <BasicTerm.h>
#include "TerminalControl.h"

class TerminalCheckbox;
typedef void (*checkboxFuncPtr)(TerminalCheckbox *checkbox);
class TerminalCheckbox: public TerminalControl
{
  public:
    TerminalCheckbox(int x, int y, int width, String ontext = "", String offtext = "");
    ~TerminalCheckbox() {}
    bool getValue();
    void setValue(bool value);
    virtual void draw(BasicTerm* term, bool focused);
    virtual bool canFocus() {
      return true;
    }
    virtual bool handleKey(uint16_t key);
    void setChangeHandler(volatile checkboxFuncPtr changehandler) {
      this->changehandler = changehandler;
    }
  private:
    bool value = false;
    String offtext = " ";
    String ontext = "X";
    checkboxFuncPtr changehandler = NULL;
};

#endif
