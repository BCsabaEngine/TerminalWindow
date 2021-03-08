#ifndef TerminalWindow_h
#define TerminalWindow_h

#include <BasicTerm.h>
#include "TerminalConfig.h"
#include "TerminalScreen.h"
#include "TerminalControl.h"

class TerminalScreen;
class TerminalControl;
class TerminalWindow
{
  public:
    TerminalWindow(String title);
    ~TerminalWindow() {
      for (byte i = 0; i < this->controlcount; i++)
      {
        delete this->controls[i];
        this->controls[i] = NULL;
      }
      this->controlcount = 0;
    }
    String getTitle() {
      return this->title;
    }
    void draw(BasicTerm* term);
    void close();
    void init();
    TerminalScreen* getScreen();
    void setScreen(TerminalScreen* screen);
    void addControl(TerminalControl* control);
    void processKey(uint16_t key);
  private:
    String title;
    TerminalScreen* screen = NULL;
    TerminalControl* controls[CONTROL_MAX_COUNT];
    byte controlcount = 0;
    byte focusedIndex = -1;
    TerminalControl* focused = NULL;
    void prevFocus();
    void nextFocus();
};

#endif
