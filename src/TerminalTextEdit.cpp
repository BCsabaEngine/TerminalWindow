#include "TerminalConfig.h"
#include "TerminalTextEdit.h"

TerminalTextEdit::TerminalTextEdit(byte x, byte y, byte width) : TerminalControl(x, y, width) {}

String TerminalTextEdit::getValue()
{
  return this->value;
}

void TerminalTextEdit::setValue(String value)
{
  this->value = value;

  if (this->changehandler)
    this->changehandler(this, value);

  this->redrawScreen();
}

void TerminalTextEdit::removeLastChar()
{
  if (int length = this->value.length())
    this->setValue(this->value.substring(0, length - 1));
}

void TerminalTextEdit::draw(BasicTerm *term, bool focused)
{
  if (!this->visible)
    return;

  this->labelDraw(term);

  String text = this->value;
  while (text.length() < this->width)
    text += " ";

#ifdef CONTROL_TEXT_DECORATOR
  text = "(" + text + ")";
#endif

  if (focused)
    term->set_attribute(BT_REVERSE);

  term->position(this->y, this->x);
  term->print(text);

  term->set_attribute(BT_NORMAL);
}

bool TerminalTextEdit::handleKey(uint16_t key)
{
  switch (key)
  {
  case 0x7F:
    this->removeLastChar();
    break;
  }

  if (
      key >= '0' && key <= '9' ||
      key >= 'a' && key <= 'z' ||
      key >= 'A' && key <= 'Z' ||
      String("., ").indexOf(key) >= 0)
  {
    char ch = key & 0xFF;
    if (this->getValue().length() < this->width)
      this->setValue(this->getValue() + ch);
  }
  return false;
}
