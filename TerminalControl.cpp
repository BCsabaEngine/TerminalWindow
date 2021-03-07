#include "TerminalControl.h"

TerminalControl::TerminalControl(int x, int y, int width)
{
  this->x = x;
  this->y = y;
  this->width = width;
}


TerminalLabel::TerminalLabel(int x, int y, int width, const char* text, HAlign halign): TerminalControl(x, y, width)
{
  this->text = text;
  this->halign = halign;
}

void TerminalLabel::draw(BasicTerm* term)
{
  char* txt = (char *)this->text;
  if (strlen(txt) > this->width)
    txt[this->width] = '\0';

  int padsize = 0;
  switch (this->halign)
  {
    case right:
      padsize = this->width - strlen(txt);
      break;
    case center:
      padsize = (this->width - strlen(txt)) / 2;
      break;
    default:
      break;
  }
  term->position(this->y, this->x + padsize);

  term->write(txt);
}
