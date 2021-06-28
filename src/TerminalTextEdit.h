#ifndef TerminalTextEdit_h
#define TerminalTextEdit_h

#include "lib/BasicTerm.h"
#include "TerminalControl.h"

#define NUMBERS String("0123456789")
#define alpha String("abcdefghijklmnopqrstuvwxyz")
#define ALPHA String("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
#define Space String(" ")

class TerminalTextEdit;
typedef void (*texteditFuncPtr)(TerminalTextEdit *textedit, String value);
class TerminalTextEdit : public TerminalControl
{
private:
  String value = "";
  String allowedchars = ALPHA + alpha + NUMBERS + Space;
  void removeLastChar();
  texteditFuncPtr changehandler = NULL;

public:
  TerminalTextEdit(byte x, byte y, byte width);
  virtual ~TerminalTextEdit() {}
  String getValue();
  void setValue(String value);
  void addAllowedChars(String allowedchars) { this->allowedchars += allowedchars; }
  void setAllowedChars(String allowedchars) { this->allowedchars = allowedchars; }
  virtual void draw(BasicTerm *term, bool focused);
  virtual bool canFocus() { return this->visible; }
  virtual bool handleKey(uint16_t key);
  void setChangeHandler(texteditFuncPtr changehandler) { this->changehandler = changehandler; }
};

#endif
