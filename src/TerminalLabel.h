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
  void setText(String text);
  virtual void draw(BasicTerm *term, bool focused);
};

#endif
