#ifndef TerminalControl_h
#define TerminalControl_h

#include <BasicTerm.h>

class TerminalWindow;
class TerminalControl
{
  protected:
    TerminalWindow* window = NULL;
    byte x;
    byte y;
    byte width;
    void redrawScreen();
    String shortString(String s);
  public:
    TerminalControl(byte x, byte y, byte width);
    TerminalWindow* getWindow();
    void setWindow(TerminalWindow* window);
    virtual void draw(BasicTerm* term, bool focused) {}
    virtual bool canFocus() {
      return false;
    }
    virtual bool handleKey(uint16_t key) {
      return false;
    }
};

enum HAlign {
  left,
  center,
  right,
};

#endif
