#include "TerminalConfig.h"
#include "TerminalLabel.h"

TerminalLabel::TerminalLabel(byte x, byte y, byte width, String text, uint8_t color, HAlign halign) : TerminalControl(x, y, width)
{
  this->setText(text);
  this->setColor(color);
  this->halign = halign;
}

void TerminalLabel::setText(String text)
{
  this->text = this->shortString(text);
  this->redrawScreen();
}

void TerminalLabel::setColor(uint8_t color)
{
  this->color = color;
  this->redrawScreen();
}

void TerminalLabel::draw(BasicTerm *term, bool focused)
{
  if (!this->visible)
    return;

  this->labelDraw(term);

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
  term->set_fg_color(this->color);
  term->print(this->text);
  term->set_fg_color(BT_WHITE);
}
