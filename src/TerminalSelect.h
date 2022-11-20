#ifndef TerminalSelect_h
#define TerminalSelect_h

#include <string.h>
#include "lib/BasicTerm.h"
#include "TerminalControl.h"

class TerminalSelect;
typedef void (*selectFuncPtr)(TerminalSelect *select, int index);
class TerminalSelect : public TerminalControl
{
private:
  int itemcount;
  String items[CONTROL_SELECT_MAX_ITEMCOUNT];
  int index = 0;
  selectFuncPtr changehandler = NULL;

public:
  TerminalSelect(byte x, byte y, byte width);
  virtual ~TerminalSelect() {}
  void setItems(String items[], int itemcount);
  int getIndex();
  void setIndex(int index, bool canunderoverflow = false);
  void setPrev();
  void setNext(bool canoverflow = false);
  virtual void draw(BasicTerm *term, bool focused);
  virtual bool canFocus() { return this->visible; }
  virtual bool handleKey(uint16_t key);
  virtual bool handleShortcut(uint16_t shortcut)
  {
    (void)shortcut;
    return false;
  }
  void setChangeHandler(selectFuncPtr changehandler) { this->changehandler = changehandler; }
};

#endif
