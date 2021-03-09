#include "TerminalControl.h"
#include "TerminalLabel.h"

TerminalLabel::TerminalLabel(byte x, byte y, byte width, String text, HAlign halign): TerminalControl(x, y, width)
{
  this->setText(text);
  this->halign = halign;
}

void TerminalLabel::setText(String text) {
  this->text = this->shortString(text);
}

void TerminalLabel::draw(BasicTerm* term, bool focused)
{
  byte padsize = 0;
  switch (this->halign)
  {
    case right:
      padsize = this->width - this->text.length();
      break;
    case center:
      padsize = (this->width - this->text.length()) / 2;
      break;
  }

  term->set_attribute(BT_NORMAL);
  term->position(this->y, this->x + padsize);
  term->print(this->text);
}
