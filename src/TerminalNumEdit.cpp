#include "TerminalConfig.h"
#include "TerminalNumEdit.h"

TerminalNumEdit::TerminalNumEdit(byte x, byte y, byte width) : TerminalControl(x, y, width) {}

int TerminalNumEdit::getValue()
{
  return this->value;
}

void TerminalNumEdit::incValue(int increment)
{
  this->setValue(this->getValue() + increment);
}

void TerminalNumEdit::setValue(int value)
{
  this->value = value;
  if (this->value > this->max)
    this->value = this->max;
  if (this->value < this->min)
    this->value = this->min;

  if (this->changehandler)
    this->changehandler(this, value);

  this->redrawScreen();
}

void TerminalNumEdit::setMinMax(int min, int max)
{
  if (min > max)
    min = max - 1;
  this->min = min;
  this->max = max;

  this->setValue(this->getValue());
}

void TerminalNumEdit::draw(BasicTerm *term, bool focused)
{
  if (!this->visible)
    return;

  this->labelDraw(term);

  String text = String(this->value);
  if (this->displaylookup)
    this->displaylookup(this, value, text);
  text.reserve(this->width + 2);

  while (text.length() < this->width)
#ifdef CONTROL_NUM_ALIGN_RIGHT
    text = " " + text;
#else
    text.concat(F(" "));
#endif

#ifdef CONTROL_NUM_DECORATOR
  text = "(" + text + ")";
#endif

  if (focused)
    term->set_attribute(BT_REVERSE);

  term->position(this->y, this->x);
  term->print(text);

  term->set_attribute(BT_NORMAL);
}

bool TerminalNumEdit::handleKey(uint16_t key)
{
  switch (key)
  {

#ifdef CONTROL_NUM_SPACE
  case ' ':
    this->incValue(1);
    return true;
#endif

#ifdef CONTROL_NUM_ENTER
  case 0xA:
  case 0xD:
    this->incValue(1);
    return true;
#endif

#ifdef CONTROL_NUM_UP_DOWN
  case BT_KEY_UP:
    this->incValue(1);
    return true;
#endif

#ifdef CONTROL_NUM_LEFT_RIGHT
  case BT_KEY_RIGHT:
    this->incValue(1);
    return true;
#endif

  case 0x2b: // numeric plus
    this->incValue(1);
    return true;

#ifdef CONTROL_NUM_UP_DOWN
  case BT_KEY_DOWN:
    this->incValue(-1);
    return true;
#endif

#ifdef CONTROL_NUM_LEFT_RIGHT
  case BT_KEY_LEFT:
    this->incValue(-1);
    return true;
#endif

  case 0x2d: // numeric minus
    this->incValue(-1);
    return true;
  }

  if (key >= '0' && key <= '9')
  {
    int value = this->getValue();
    if (millis() - this->lastKey > CONTROL_NUM_MAXLATENCY_MS)
      value = 0;
    this->setValue(value * 10 + key - 0x30);

    this->lastKey = millis();
  }
  return false;
}
