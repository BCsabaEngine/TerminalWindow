#ifndef TerminalTextEdit_h
#define TerminalTextEdit_h

#include "lib/BasicTerm.h"
#include "TerminalControl.h"

class TerminalTextEdit;
typedef void (*texteditFuncPtr)(TerminalTextEdit *textedit, String value);
//typedef void (*numeditDisplayLookupFuncPtr)(TerminalNumEdit *numedit, int value, String &displaytext);
class TerminalTextEdit : public TerminalControl
{
private:
  String value = "";
  void removeLastChar();
  texteditFuncPtr changehandler = NULL;
  //numeditDisplayLookupFuncPtr displaylookup = NULL;

public:
  TerminalTextEdit(byte x, byte y, byte width);
  virtual ~TerminalTextEdit() {}
  String getValue();
  void setValue(String value);
  virtual void draw(BasicTerm *term, bool focused);
  virtual bool canFocus() { return this->visible; }
  virtual bool handleKey(uint16_t key);
  void setChangeHandler(texteditFuncPtr changehandler) { this->changehandler = changehandler; }
  //void setDisplayLookup(numeditDisplayLookupFuncPtr displaylookup) { this->displaylookup = displaylookup; }
};

#endif
