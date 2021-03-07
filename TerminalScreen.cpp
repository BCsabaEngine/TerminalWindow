#include "TerminalScreen.h"
#include "TerminalWindow.h"
#ifdef DEBUG
#include <MemoryFree.h>
#endif

TerminalScreen::TerminalScreen(char* title)
{
  this->term = new BasicTerm(&Serial);
  this->windowindex = -1;
  this->title = title;

  term->init();
  term->show_cursor(false);
}

void TerminalScreen::addWindow(TerminalWindow* window)
{
  window->setScreen(this);

  window->init();

  this->windowindex++;
  this->windows[this->windowindex] = window;
}

void(* resetFunc) (void) = 0;

void TerminalScreen::popWindow()
{
  if (this->windowindex >= 0)
  {
    delete this->windows[this->windowindex];
    this->windowindex--;

    this->draw();
  }

  if (this->windowindex < 0)
  {
    term->cls();
    term->position(0, 0);
    term->print(F("No window, reset..."));
    term->flush();

    delay(1500);

    resetFunc();
  }
}

TerminalWindow* TerminalScreen::getTopWindow()
{
  if (this->windowindex >= 0)
    return this->windows[this->windowindex];
}

void TerminalScreen::draw()
{
  term->cls();

  if (!this->getTopWindow())
  {
    term->position(0, 0);
    term->print(F("No window!"));
  }
  else
  {
    term->position(0, 0);
    term->write(this->title);
    term->print(F(" ("));
    term->write(__DATE__);
    term->print(F(")"));

#ifdef DEBUG
    term->print(F(" F: "));
    term->write(String(freeMemory()).c_str());
    term->print(F(" K: "));
    term->write(String(this->key, HEX).c_str());
#endif

    term->position(1, 0);
    for (int i = 0; i < strlen(this->title) + 14; i++)
      term->print(F("*"));

    this->getTopWindow()->draw(term);
  }
}

void TerminalScreen::loop()
{
  this->key = this->term->get_key();
  if (this->key != -1)
    this->getTopWindow()->processKey(this->key);

  this->draw();
}
