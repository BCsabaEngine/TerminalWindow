#ifndef TerminalLabelMultiLine_h
#define TerminalLabelMultiLine_h

#include "lib/BasicTerm.h"
#include "TerminalControl.h"

class TerminalLabelMultiLine : public TerminalControl
{
private:
  byte height;
  int linecount;
  String lines[CONTROL_LABELML_MAX_HEIGHT];
  uint8_t color = BT_WHITE;

public:
  TerminalLabelMultiLine(byte x, byte y, byte width, byte height, uint8_t color = BT_WHITE);
  virtual ~TerminalLabelMultiLine() {}
  void clearLines();
  void setLines(String lines[], int linecount);
  void setColor(uint8_t color);
  virtual void draw(BasicTerm *term, bool focused);
  virtual bool canFocus() { return false; }
  virtual bool handleKey(uint16_t key)
  {
    (void)key;
    return false;
  }
  virtual bool handleShortcut(uint16_t shortcut)
  {
    (void)shortcut;
    return false;
  }
};

#endif
