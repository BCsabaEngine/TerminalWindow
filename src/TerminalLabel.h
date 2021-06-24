#ifndef TerminalLabel_h
#define TerminalLabel_h

#include "lib/BasicTerm.h"
#include "TerminalControl.h"

class TerminalLabel : public TerminalControl
{
private:
  String text;
  HAlign halign;

public:
  TerminalLabel(byte x, byte y, byte width, String text, HAlign halign = hAlignLeft);
  virtual ~TerminalLabel() {}
  void setText(String text);
  virtual void draw(BasicTerm *term, bool focused);
  virtual bool canFocus() { return false; }
  virtual bool handleKey(uint16_t key)
  {
    (void)key;
    return false;
  }
};

#endif
