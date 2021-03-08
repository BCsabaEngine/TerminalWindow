#ifndef TerminalControl_h
#define TerminalControl_h

#include <BasicTerm.h>

class TerminalWindow;
class TerminalControl
{
  public:
    TerminalControl(int x, int y, int width);
    ~TerminalControl() {}
    TerminalWindow* getWindow();
    void setWindow(TerminalWindow* window);
    virtual void draw(BasicTerm* term, bool focused);
    virtual bool canFocus() {
      return false;
    }
    virtual bool handleKey(uint16_t key) {
      return false;
    }
  protected:
    TerminalWindow* window = NULL;
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
