#include "TerminalWindow.h"

TerminalWindow::TerminalWindow()
{
}

void TerminalWindow::draw(BasicTerm* term)
{
  for (int i = 0; i < this->_controlcount; i++)
    this->_controls[i]->draw(term);
}

void TerminalWindow::close()
{
  this->_screen->popWindow();
}

void TerminalWindow::setScreen(TerminalScreen* screen)
{
  this->_screen = screen;
}

void TerminalWindow::addControl(TerminalControl* control)
{
  if (this->_controlcount < CONTROL_MAX_COUNT)
  {
    this->_controls[this->_controlcount] = control;
    this->_controlcount++;
  }
}
