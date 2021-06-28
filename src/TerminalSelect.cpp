#include "TerminalConfig.h"
#include "TerminalSelect.h"

TerminalSelect::TerminalSelect(byte x, byte y, byte width) : TerminalControl(x, y, width) {}

void TerminalSelect::setItems(String items[], int itemcount)
{
  this->itemcount = itemcount;
  for (int i = 0; i < itemcount; i++)
    this->items[i] = items[i];
}

int TerminalSelect::getIndex()
{
  return this->index;
}

void TerminalSelect::setIndex(int index, bool canunderoverflow)
{
  this->index = index;
  if (canunderoverflow)
  {
    while (this->index > this->itemcount - 1)
      this->index = 0;
    if (this->index < 0)
      this->index = this->itemcount - 1;
  }
  else
  {
    if (this->index > this->itemcount - 1)
      this->index = this->itemcount - 1;
    if (this->index < 0)
      this->index = 0;
  }

  if (this->changehandler)
    this->changehandler(this, this->index);

  this->redrawScreen();
}

void TerminalSelect::setPrev()
{
  this->setIndex(this->getIndex() - 1);
}

void TerminalSelect::setNext(bool canoverflow)
{
  this->setIndex(this->getIndex() + 1, canoverflow);
}

void TerminalSelect::draw(BasicTerm *term, bool focused)
{
  if (!this->visible)
    return;

  this->labelDraw(term);

  String text = this->items[this->index];
  while (text.length() < this->width)
    text += " ";
#ifdef CONTROL_SELECT_DECORATOR
  text = "<" + text + ">";
#endif

  if (focused)
    term->set_attribute(BT_REVERSE);

  term->position(this->y, this->x);
  term->print(text);

  term->set_attribute(BT_NORMAL);
}

bool TerminalSelect::handleKey(uint16_t key)
{
  switch (key)
  {

#ifdef CONTROL_SELECT_SPACE
  case ' ':
    this->setNext(true);
    return true;
#endif

#ifdef CONTROL_SELECT_ENTER
  case 0xA:
  case 0xD:
    this->setNext(true);
    return true;
#endif

#ifdef CONTROL_SELECT_UP_DOWN
  case BT_KEY_UP:
    this->setNext();
    return true;
#endif

#ifdef CONTROL_SELECT_LEFT_RIGHT
  case BT_KEY_RIGHT:
    this->setNext();
    return true;
#endif

  case 0x2b: // numeric plus
    this->setNext();
    return true;

#ifdef CONTROL_SELECT_UP_DOWN
  case BT_KEY_DOWN:
    this->setPrev();
    return true;
#endif

#ifdef CONTROL_SELECT_LEFT_RIGHT
  case BT_KEY_LEFT:
    this->setPrev();
    return true;
#endif

  case 0x2d: // numeric minus
    this->setPrev();
    return true;
  }

  return false;
}
