#include "TerminalConfig.h"
#include "TerminalButton.h"

TerminalButton::TerminalButton(byte x, byte y, byte width, String text) : TerminalControl(x, y, width)
{
  this->setText(text);
}

void TerminalButton::setText(String text)
{
  this->text = this->shortString(text);
  this->redrawScreen();
}

void TerminalButton::draw(BasicTerm *term, bool focused)
{
  if (!this->visible)
    return;

  byte padsize = (this->width - this->text.length()) / 2;

  if (focused)
    term->set_attribute(BT_REVERSE);

  term->position(this->y, this->x);
  for (byte i = 0; i < this->width - 1; i++)
    term->print(F(" "));

#ifdef CONTROL_BUTTON_DECORATOR
  term->position(this->y, this->x);
  term->print(F("|"));
#endif

  term->position(this->y, this->x + padsize);
  term->print(this->text);

#ifdef CONTROL_BUTTON_DECORATOR
  term->position(this->y, this->x + this->width - 1);
  term->print(F("|"));
#endif

  term->set_attribute(BT_NORMAL);
}

bool TerminalButton::handleKey(uint16_t key)
{
  switch (key)
  {

#ifdef CONTROL_BUTTON_SPACE
  case ' ':
    if (this->clickhandler)
      this->clickhandler(this);
    return true;
#endif

#ifdef CONTROL_BUTTON_ENTER
  case 0xA:
  case 0xD:
    if (this->clickhandler)
      this->clickhandler(this);
    return true;
#endif
  }
  return false;
}
