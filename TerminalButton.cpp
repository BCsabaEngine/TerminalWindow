#include "TerminalControl.h"
#include "TerminalButton.h"

TerminalButton::TerminalButton(int x, int y, int width, const char* text, HAlign halign): TerminalControl(x, y, width)
{
  this->text = (char*)text;
  if (strlen(this->text) > this->width)
    this->text[this->width] = '\0';

  this->halign = halign;
}

void TerminalButton::draw(BasicTerm* term, bool focused)
{
  int padsize = 0;
  switch (this->halign)
  {
    case right:
      padsize = this->width - strlen(this->text);
      break;
    case center:
      padsize = (this->width - strlen(this->text)) / 2;
      break;
  }
  term->position(this->y, this->x);
  term->write("|");

  term->position(this->y, this->x + padsize);
  term->write(this->text);

  term->position(this->y, this->x + this->width - 1);
  term->write("|");
}
