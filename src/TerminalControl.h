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
  bool visible = true;
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
  virtual ~TerminalControl() {}
  bool getVisible();
  void setVisible(bool visible);
  void hide() { this->setVisible(false); }
  void show() { this->setVisible(true); }
  void addLabel(String text, LabelPos labelpos);
  TerminalScreen *getScreen();
  TerminalWindow *getWindow();
  void closeWindow();
  void addWindow(TerminalWindow *window);
  void setWindow(TerminalWindow *window);
  virtual void draw(BasicTerm *term, bool focused) = 0;
  virtual bool canFocus() = 0;
  virtual bool handleKey(uint16_t key) = 0;
};

#endif
