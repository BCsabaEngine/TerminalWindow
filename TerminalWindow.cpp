#include "TerminalWindow.h"

TerminalWindow::TerminalWindow()
{
}

void TerminalWindow::draw(BasicTerm* term)
{
  for (byte i = 0; i < this->controlcount; i++)
    this->controls[i]->draw(term, this->focusedIndex == i);
}

void TerminalWindow::close()
{
  this->getScreen()->popWindow();
}

void TerminalWindow::init()
{
  if (!this->focused)
    for (byte i = 0; i < this->controlcount; i++)
      if (this->controls[i]->canFocus())
      {
        this->focused = this->controls[i];
        this->focusedIndex = i;
        break;
      }
}

void TerminalWindow::prevFocus()
{
  byte actual = this->focusedIndex - 1;

  while (actual != this->focusedIndex)
  {
    if (actual < 0)
      actual = this->focusedIndex - 1;

    if (this->controls[actual]->canFocus())
    {
      this->focused = this->controls[actual];
      this->focusedIndex = actual;
      return;
    }

    actual--;
  }
}

void TerminalWindow::nextFocus()
{
  byte actual = this->focusedIndex + 1;

  while (actual != this->focusedIndex)
  {
    if (actual >= this->controlcount)
      actual = 0;

    if (this->controls[actual]->canFocus())
    {
      this->focused = this->controls[actual];
      this->focusedIndex = actual;
      return;
    }

    actual++;
  }
}

void TerminalWindow::processKey(uint16_t key)
{
  if (this->focusedIndex < 0)
    return;

  if (key == 0x1b)
  {
    this->close();
    return;
  }

  bool handled = this->controls[this->focusedIndex]->handleKey(key);
  if (!handled)
    switch (key)
    {
      case 0x9:   //TAB
      case BT_KEY_DOWN:
      case BT_KEY_RIGHT:
        this->nextFocus();
        break;
      case BT_KEY_UP:
      case BT_KEY_LEFT:
        this->prevFocus();
        break;
    }
}

TerminalScreen* TerminalWindow::getScreen()
{
  return this->screen;
}

void TerminalWindow::setScreen(TerminalScreen* screen)
{
  this->screen = screen;
}

void TerminalWindow::addControl(TerminalControl* control)
{
  if (this->controlcount < CONTROL_MAX_COUNT)
  {
    control->setWindow(this);

    this->controls[this->controlcount] = control;
    this->controlcount++;
  }
}
