#include "TerminalControl.h"
#include "TerminalLabel.h"

TerminalLabel::TerminalLabel(int x, int y, int width, String text, HAlign halign): TerminalControl(x, y, width)
{
  this->setText(text);
  this->halign = halign;
}

void TerminalLabel::setText(String text) {
  if (text.length() > this->width)
    text = text.substring(this->width);
  this->text = text;
}

void TerminalLabel::draw(BasicTerm* term, bool focused)
{
  int padsize = 0;
  switch (this->halign)
  {
    case right:
      padsize = this->width - this->text.length();
      break;
    case center:
      padsize = (this->width - this->text.length()) / 2;
      break;
  }

  term->position(this->y, this->x + padsize);
  term->set_attribute(BT_NORMAL);
  term->print(this->text);
}
