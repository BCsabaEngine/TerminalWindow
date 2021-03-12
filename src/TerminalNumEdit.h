#ifndef TerminalNumEdit_h
#define TerminalNumEdit_h

#include "BasicTerm.h"
#include "TerminalControl.h"

class TerminalNumEdit;
typedef void (*numeditFuncPtr)(TerminalNumEdit *numedit, int value);
class TerminalNumEdit: public TerminalControl {
  private:
    int value = 0;
    int min = 0;
    int max = 1000;
    unsigned long lastKey = 0;
    numeditFuncPtr changehandler = NULL;
  public:
    TerminalNumEdit(byte x, byte y, byte width);
    int getValue();
    void incValue(int increment = 1);
    void decValue(int decrement = 1) { this->incValue(-1 * decrement); };
    void setValue(int value);
    void setMinMax(int min, int max);
    virtual void draw(BasicTerm* term, bool focused);
    virtual bool canFocus() {
      return true;
    }
    virtual bool handleKey(uint16_t key);
    void setChangeHandler(numeditFuncPtr changehandler) {
      this->changehandler = changehandler;
    }
};

#endif
