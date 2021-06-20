#ifndef TerminalControl_h
#define TerminalControl_h

#include "lib/BasicTerm.h"

enum HAlign
{
  hAlignLeft,
  hAlignCenter,
  hAlignRight,
};

enum LabelPos
{
  labelPosTop,
  labelPosLeft,
};

class TerminalWindow;
class TerminalScreen;
class TerminalControl
{
protected:
  TerminalWindow *window = NULL;
  byte x;
  byte y;
  byte width;
  String labelText;
  LabelPos labelPos;
  void labelDraw(BasicTerm *term);
  void redrawScreen();
  String shortString(String s);

public:
  TerminalControl(byte x, byte y, byte width);
  void addLabel(String text, LabelPos labelpos);
  TerminalScreen *getScreen();
  TerminalWindow *getWindow();
  void closeWindow();
  void addWindow(TerminalWindow *window);
  void setWindow(TerminalWindow *window);
  virtual void draw(BasicTerm *term, bool focused) {}
  virtual bool canFocus()
  {
    return false;
  }
  virtual bool handleKey(uint16_t key)
  {
    return false;
  }
};

#endif
