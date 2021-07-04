#ifndef TerminalNumEdit_h
#define TerminalNumEdit_h

#include "lib/BasicTerm.h"
#include "TerminalControl.h"

class TerminalNumEdit;
typedef void (*numeditFuncPtr)(TerminalNumEdit *numedit, int value);
typedef void (*numeditDisplayLookupFuncPtr)(TerminalNumEdit *numedit, int value, String &displaytext);
typedef void (*numeditAllowedValueFuncPtr)(TerminalNumEdit *numedit, int value, bool &allowed);
class TerminalNumEdit : public TerminalControl
{
private:
  int value = 0;
  int min = 0;
  int max = 1000;
  unsigned long lastKey = 0;
  numeditFuncPtr changehandler = NULL;
  numeditDisplayLookupFuncPtr displaylookup = NULL;
  numeditAllowedValueFuncPtr allowedvalue = NULL;

public:
  TerminalNumEdit(byte x, byte y, byte width);
  virtual ~TerminalNumEdit() {}
  int getValue();
  void incValue(int increment = 1);
  void decValue(int decrement = 1) { this->incValue(-1 * decrement); };
  void setValue(int value, bool scanup = true);
  void setMinMax(int min, int max);
  virtual void draw(BasicTerm *term, bool focused);
  virtual bool canFocus() { return this->visible; }
  virtual bool handleKey(uint16_t key);
  void setChangeHandler(numeditFuncPtr changehandler) { this->changehandler = changehandler; }
  void setDisplayLookup(numeditDisplayLookupFuncPtr displaylookup) { this->displaylookup = displaylookup; }
  void setAllowedValue(numeditAllowedValueFuncPtr allowedvalue) { this->allowedvalue = allowedvalue; }
};

#endif
