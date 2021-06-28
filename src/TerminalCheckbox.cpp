#include "TerminalConfig.h"
#include "TerminalCheckbox.h"

TerminalCheckbox::TerminalCheckbox(byte x, byte y, byte width, String ontext, String offtext) : TerminalControl(x, y, width)
{
  this->offtext = this->shortString(offtext);
  this->ontext = this->shortString(ontext);
}

bool TerminalCheckbox::getValue()
{
  return this->value;
}

void TerminalCheckbox::setValue(bool value)
{
  this->value = value;

  if (this->changehandler)
    this->changehandler(this, value);

  this->redrawScreen();
}

void TerminalCheckbox::draw(BasicTerm *term, bool focused)
{
  if (!this->visible)
    return;

  this->labelDraw(term);

#ifdef CONTROL_CHECKBOX_DECORATOR
  String text = "[" + (this->value ? this->ontext : this->offtext) + "]";
#else
  String text = this->value ? this->ontext : this->offtext;
#endif
  if (focused)
    term->set_attribute(BT_REVERSE);

  term->position(this->y, this->x);
  term->print(text);

  term->set_attribute(BT_NORMAL);
}

bool TerminalCheckbox::handleKey(uint16_t key)
{
  switch (key)
  {

#ifdef CONTROL_CHECKBOX_SPACE
  case ' ':
    this->setValue(!this->getValue());
    return true;
#endif

#ifdef CONTROL_CHECKBOX_ENTER
  case 0xA:
  case 0xD:
    this->setValue(!this->getValue());
    return true;
#endif

#ifdef CONTROL_CHECKBOX_UP_DOWN
  case BT_KEY_UP:
    this->setValue(true);
    return true;
  case BT_KEY_DOWN:
    this->setValue(false);
    return true;
#endif

#ifdef CONTROL_CHECKBOX_LEFT_RIGHT
  case BT_KEY_LEFT:
    this->setValue(false);
    return true;
  case BT_KEY_RIGHT:
    this->setValue(true);
    return true;
#endif
  }
  return false;
}
