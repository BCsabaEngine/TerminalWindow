#include "TerminalControl.h"
#include "TerminalButton.h"

TerminalButton::TerminalButton(int x, int y, int width, String text): TerminalControl(x, y, width)
{
  this->setText(text);
}

void TerminalButton::setText(String text) {
  if (text.length() > this->width)
    text = text.substring(this->width);
  this->text = text;
}

void TerminalButton::draw(BasicTerm* term, bool focused)
{
  int padsize = (this->width - this->text.length()) / 2;

  if (focused)
    term->set_attribute(BT_REVERSE);

  term->position(this->y, this->x);
  for (int i = 0; i < this->width - 1; i++)
    term->print(F(" "));

  term->position(this->y, this->x);
  term->print(F("|"));

  term->position(this->y, this->x + padsize);
  term->print(this->text);

  term->position(this->y, this->x + this->width - 1);
  term->print(F("|"));

  term->set_attribute(BT_NORMAL);
}

bool TerminalButton::handleKey(uint16_t key)
{
  switch (key)
  {
    case 0xA:
    case ' ':
      if (this->clickhandler)
        this->clickhandler(this);
      break;
  }
  return false;
}
