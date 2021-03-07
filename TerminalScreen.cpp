#include "TerminalScreen.h"
#include "TerminalWindow.h"

TerminalScreen::TerminalScreen(char* title)
{
  this->term = new BasicTerm(&Serial);
  this->windowindex = -1;
  this->title = title;

  term->init();
}

void TerminalScreen::addWindow(TerminalWindow* window)
{
  window->setScreen(this);

  this->windowindex++;
  this->windows[this->windowindex] = window;
}

void TerminalScreen::popWindow()
{
  if (this->windowindex >= 0)
    delete this->windows[this->windowindex];
  this->windowindex--;

  this->draw();
}

TerminalWindow* TerminalScreen::getTopWindow()
{
  if (this->windowindex >= 0)
    return this->windows[this->windowindex];
}

void TerminalScreen::draw()
{
  term->cls();

  term->position(0, 0);
  term->write(this->title);
  term->write(" (");
  term->write(__DATE__);
  term->write(") F: ");
  term->write(String(freeMemory()).c_str());

  term->position(1, 0);
  for (int i = 0; i < strlen(this->title) + 14 + 9; i++)
    term->write("*");

  this->getTopWindow()->draw(term);
}

void TerminalScreen::loop()
{
  this->draw();
}
