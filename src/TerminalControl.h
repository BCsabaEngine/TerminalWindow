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
class TerminalControl;
typedef void (*controlFuncPtr)(TerminalControl *control);
class TerminalControl
{
protected:
  TerminalWindow *window = NULL;
  bool visible = true;
  byte x;
  byte y;
  byte width;
  String labelText = "";
  LabelPos labelPos;
  uint8_t labelColor = BT_WHITE;
  void labelDraw(BasicTerm *term);
  void redrawScreen();
  String shortString(String s);
  uint8_t _tag8;
  uint16_t _tag16;
  uint32_t _tag32;
  void *_tagp;
  controlFuncPtr enterhandler = NULL;
  controlFuncPtr leavehandler = NULL;

public:
  TerminalControl(byte x, byte y, byte width);
  virtual ~TerminalControl() {}
  bool getVisible() { return this->visible; }
  void setVisible(bool visible);
  void hide() { this->setVisible(false); }
  void show() { this->setVisible(true); }
  void addLabel(String text, LabelPos labelpos, uint8_t color = BT_WHITE);
  uint8_t tag8() { return this->_tag8; }
  void tag8(uint8_t tag) { this->_tag8 = tag; }
  uint16_t tag16() { return this->_tag16; }
  void tag16(uint16_t tag) { this->_tag16 = tag; }
  uint32_t tag32() { return this->_tag32; }
  void tag32(uint32_t tag) { this->_tag32 = tag; }
  void *tagP() { return this->_tagp; }
  void tagP(void *tag) { this->_tagp = tag; }
  byte GetX() { return this->x; }
  byte GetY() { return this->y; }
  void SetX(byte x) { this->x = x; }
  void SetY(byte y) { this->y = y; }
  void SetMinX(byte x)
  {
    if (this->x < x)
      this->x = x;
  }
  void SetMinY(byte y)
  {
    if (this->y < y)
      this->y = y;
  }
  void SetMaxX(byte x)
  {
    if (this->x > x)
      this->x = x;
  }
  void SetMaxY(byte y)
  {
    if (this->y > y)
      this->y = y;
  }
  TerminalScreen *getScreen();
  TerminalWindow *getWindow();
  void closeWindow();
  void addWindow(TerminalWindow *window);
  void setWindow(TerminalWindow *window);
  virtual void draw(BasicTerm *term, bool focused) = 0;
  virtual bool canFocus() = 0;
  virtual bool handleKey(uint16_t key) = 0;
  virtual bool handleShortcut(uint16_t shortcut) = 0;
  void focus();
  void focusEnter()
  {
    if (this->enterhandler)
      this->enterhandler(this);
  }
  void focusLeave()
  {
    if (this->leavehandler)
      this->leavehandler(this);
  }
  void setEnterHandler(controlFuncPtr enterhandler) { this->enterhandler = enterhandler; }
  void setLeaveHandler(controlFuncPtr leavehandler) { this->leavehandler = leavehandler; }
};

#endif
