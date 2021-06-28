#ifndef TerminalTextEdit_h
#define TerminalTextEdit_h

#include "lib/BasicTerm.h"
#include "TerminalControl.h"

class TerminalTextEdit;
typedef void (*texteditFuncPtr)(TerminalTextEdit *textedit, String value);
class TerminalTextEdit : public TerminalControl
{
private:
  String value = "";
  void appendChar(char chr);
  void removeLastChar();
  texteditFuncPtr changehandler = NULL;
  bool allowed_lower_alpha = true;
  bool allowed_upper_alpha = true;
  bool allowed_numbers = true;
  bool allowed_space = false;
  String allowed_extrachars = "";

public:
  TerminalTextEdit(byte x, byte y, byte width);
  virtual ~TerminalTextEdit() {}
  String getValue();
  void setValue(String value);
  void setAllowedChars(bool lower_alpha, bool upper_alpha, bool numbers, bool space, String extrachars = "");
  virtual void draw(BasicTerm *term, bool focused);
  virtual bool canFocus() { return this->visible; }
  virtual bool handleKey(uint16_t key);
  void setChangeHandler(texteditFuncPtr changehandler) { this->changehandler = changehandler; }
};

#endif
