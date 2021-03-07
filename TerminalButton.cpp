#include "TerminalControl.h"
#include "TerminalButton.h"

TerminalButton::TerminalButton(int x, int y, int width, const char* text): TerminalControl(x, y, width)
{
  this->text = (char*)text;
  if (strlen(this->text) > this->width)
    this->text[this->width] = '\0';
}

void TerminalButton::draw(BasicTerm* term, bool focused)
{
  int padsize = (this->width - strlen(this->text)) / 2;;

  if (focused)
    term->set_attribute(BT_REVERSE);

  term->position(this->y, this->x);
  for (int i = 0; i < this->width - 1; i++)
    term->write(" ");

  term->position(this->y, this->x);
  term->write("|");

  term->position(this->y, this->x + padsize);
  term->write(this->text);

  term->position(this->y, this->x + this->width - 1);
  term->write("|");

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
