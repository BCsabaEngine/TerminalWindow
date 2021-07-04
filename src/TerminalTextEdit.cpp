#include "TerminalConfig.h"
#include "TerminalTextEdit.h"

TerminalTextEdit::TerminalTextEdit(byte x, byte y, byte width) : TerminalControl(x, y, width)
{
  this->value.reserve(width);
}

String TerminalTextEdit::getValue()
{
  return this->value;
}

void TerminalTextEdit::setValue(String value)
{
  String origvalue = this->value;

  this->value = value;

  if (this->changehandler)
    if (origvalue != this->value)
      this->changehandler(this, value);

  this->redrawScreen();
}

void TerminalTextEdit::appendChar(char chr)
{
  if (this->value.length() < this->width)
    this->setValue(this->value + chr);
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
  text.reserve(this->width + 2);
  while (text.length() < this->width)
    text.concat(F(" "));

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
    return true;
  }

  char ch = key & 0xFF;
  if (
      (this->allowed_lower_alpha && ch >= 'a' && ch <= 'z') ||
      (this->allowed_upper_alpha && ch >= 'A' && ch <= 'Z') ||
      (this->allowed_numbers && ch >= '0' && ch <= '9') ||
      (this->allowed_space && ch == 0x20) ||
      this->allowed_extrachars.indexOf(ch) >= 0)
  {
    this->appendChar(ch);
    return true;
  }

  return false;
}

void TerminalTextEdit::setAllowedChars(bool lower_alpha, bool upper_alpha, bool numbers, bool space, String extrachars)
{
  this->allowed_lower_alpha = lower_alpha;
  this->allowed_upper_alpha = upper_alpha;
  this->allowed_numbers = numbers;
  this->allowed_space = space;
  this->allowed_extrachars = extrachars;
}
