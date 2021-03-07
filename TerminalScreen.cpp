#include "TerminalScreen.h"
#include "TerminalWindow.h"

TerminalScreen::TerminalScreen()
{
  this->term = new BasicTerm(&Serial);
  this->_windowindex = -1;

  term->init();
}

void TerminalScreen::addWindow(TerminalWindow* window)
{
  this->_windowindex++;
  this->_windows[this->_windowindex] = window;
}

void TerminalScreen::popWindow()
{
  if (this->_windowindex >= 0)
    delete this->_windows[this->_windowindex];
  this->_windowindex--;

  this->draw();
}

TerminalWindow* TerminalScreen::getTopWindow()
{
  if (this->_windowindex >= 0)
    return this->_windows[this->_windowindex];
}

void TerminalScreen::draw()
{
  term->cls();
  this->getTopWindow()->draw(term);
}

void TerminalScreen::loop()
{
  this->draw();
}
