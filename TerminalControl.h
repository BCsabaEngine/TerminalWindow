#ifndef TerminalControl_h
#define TerminalControl_h

#include <BasicTerm.h>

class TerminalWindow;
class TerminalControl
{
  public:
    TerminalControl(int x, int y, int width);
    TerminalWindow* getWindow();
    void setWindow(TerminalWindow* window);
    virtual void draw(BasicTerm* term, bool focused);
    virtual bool canFocus() {
      return false;
    }
  protected:
    TerminalWindow* window;
    int x;
    int y;
    int width;
};

enum HAlign {
  left,
  center,
  right,
};

#endif
