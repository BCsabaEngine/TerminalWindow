#include "TerminalConfig.h"
#include "TerminalLabel.h"

TerminalLabel::TerminalLabel(byte x, byte y, byte width, String text, HAlign halign) : TerminalControl(x, y, width)
{
  this->setText(text);
  this->halign = halign;
}

void TerminalLabel::setText(String text)
{
  this->text = this->shortString(text);
  this->redrawScreen();
}

void TerminalLabel::draw(BasicTerm *term, bool focused)
{
  if (!this->visible)
    return;

  byte padsize = 0;
  switch (this->halign)
  {
  case hAlignRight:
    padsize = this->width - this->text.length();
    break;
  case hAlignCenter:
    padsize = (this->width - this->text.length()) / 2;
    break;
  default:
    break;
  }

  if (focused)
    term->set_attribute(BT_NORMAL);
  term->set_attribute(BT_NORMAL);

  term->position(this->y, this->x + padsize);
  term->print(this->text);
}
