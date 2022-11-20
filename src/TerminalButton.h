#ifndef TerminalButton_h
#define TerminalButton_h

#include "lib/BasicTerm.h"
#include "TerminalControl.h"

class TerminalButton;
typedef void (*buttonFuncPtr)(TerminalButton *button);
class TerminalButton : public TerminalControl
{
private:
  String text;
  uint16_t shortcut = 0;
  buttonFuncPtr clickhandler = NULL;

public:
  TerminalButton(byte x, byte y, byte width, String text,uint16_t shortcut = 0);
  virtual ~TerminalButton() {}
  void setText(String text);
  virtual void draw(BasicTerm *term, bool focused);
  virtual bool canFocus() { return this->visible; }
  virtual bool handleKey(uint16_t key);
  virtual bool handleShortcut(uint16_t shortcut);
  void setClickHandler(buttonFuncPtr clickhandler) { this->clickhandler = clickhandler; }
};

#endif
