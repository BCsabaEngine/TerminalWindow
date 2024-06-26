#ifndef TerminalWindow_h
#define TerminalWindow_h

#include "lib/BasicTerm.h"
#include "TerminalConfig.h"
#include "TerminalScreen.h"
#include "TerminalControl.h"

class TerminalScreen;
class TerminalControl;
class TerminalWindow
{
private:
  TerminalControl *controls[CONTROL_MAX_COUNT];
  TerminalControl *runtimecontrols[CONTROL_MAX_COUNT];
  TerminalScreen *screen = NULL;
  int controlcount = 0;
  int runtimecontrolcount = 0;
  int focusedIndex = -1;
  void prevFocus();
  void nextFocus();

public:
  TerminalWindow(String title);
  virtual ~TerminalWindow();
  String title;
  void draw(BasicTerm *term);
  virtual void loop(){};
  virtual bool canCloseByEscape() { return true; };
  void close();
  void init();
  void redrawScreen();
  TerminalScreen *getScreen();
  void setScreen(TerminalScreen *screen);
  void addControl(TerminalControl *control);
  void addRuntimeControl(TerminalControl *control);
  void processKey(uint16_t key);
  void dropFocusIfThis(TerminalControl *control);
  void firstFocus();
  void lastFocus();
  void focusAt(int index);
  void focusControl(TerminalControl *control);
};

#endif
