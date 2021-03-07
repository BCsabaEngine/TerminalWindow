#include "TerminalWindow.h"

TerminalWindow::TerminalWindow()
{
}

void TerminalWindow::draw(BasicTerm* term)
{
  for (int i = 0; i < this->controlcount; i++)
    this->controls[i]->draw(term);
}

void TerminalWindow::close()
{
  this->screen->popWindow();
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
