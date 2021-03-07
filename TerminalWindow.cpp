#include "TerminalWindow.h"

TerminalWindow::TerminalWindow()
{
}

void TerminalWindow::draw(BasicTerm* term)
{
  for (int i = 0; i < this->controlcount; i++)
    this->controls[i]->draw(term, this->focused == this->controls[i]);
}

void TerminalWindow::close()
{
  this->screen->popWindow();
}

void TerminalWindow::init()
{
  if (!this->focused)
    for (int i = 0; i < this->controlcount; i++)
      if (this->controls[i]->canFocus())
      {
        this->focused = this->controls[i];
        break;
      }
}

void TerminalWindow::prevFocus()
{

}

void TerminalWindow::nextFocus()
{

}

void TerminalWindow::processKey(uint16_t key)
{
  for (int i = 0; i < this->controlcount; i++)
    if (this->focused == this->controls[i])
    {
      bool handled = this->controls[i]->handleKey(key);
      if (!handled)
        switch (key)
        {
          case 0x9:   //TAB
          case 0x102: //Down
          case 0x105: //Right
            this->nextFocus();
            break;
          case 0x103: //Up
          case 0x104: //Left
            this->prevFocus();
            break;
        }
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
