#include "TerminalControl.h"
#include "TerminalCheckbox.h"

TerminalCheckbox::TerminalCheckbox(byte x, byte y, byte width, String ontext, String offtext): TerminalControl(x, y, width) {
  this->offtext = this->shortString(offtext);
  this->ontext = this->shortString(ontext);
}

bool TerminalCheckbox::getValue() {
  return this->value;
}

void TerminalCheckbox::setValue(bool value) {
  this->value = value;

  if (this->changehandler)
    this->changehandler(this, value);

  this->redrawScreen();
}

void TerminalCheckbox::draw(BasicTerm* term, bool focused) {
  String text = "[" + (this->value ? this->ontext : this->offtext) + "]";

  if (focused)
    term->set_attribute(BT_REVERSE);

  term->position(this->y, this->x);
  term->print(text);

  term->set_attribute(BT_NORMAL);
}

bool TerminalCheckbox::handleKey(uint16_t key) {
  switch (key) {
    case ' ':
      this->setValue(!this->getValue());
      return true;
    case 'y':
      this->setValue(true);
      return true;
    case 'n':
      this->setValue(false);
      return true;
  }
  return false;
}
