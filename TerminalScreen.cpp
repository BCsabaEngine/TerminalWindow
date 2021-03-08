#include "TerminalScreen.h"
#include "TerminalWindow.h"
#ifdef DEBUG
#include <MemoryFree.h>
#endif

TerminalScreen::TerminalScreen(String title)
{
  this->windowindex = -1;
  this->title = title;

  this->term = new BasicTerm(&Serial);
  this->term->init();
  this->term->show_cursor(false);
}

TerminalScreen::~TerminalScreen()
{
  if (this->term)
  {
    delete this->term;
    this->term = NULL;
  }
}

void TerminalScreen::addWindow(TerminalWindow* window)
{
  window->setScreen(this);

  window->init();

  this->windowindex++;
  this->windows[this->windowindex] = window;

  this->draw();
}

void(* rebootFunc) (void) = 0;

void TerminalScreen::popWindow()
{
  if (this->windowindex >= 0)
  {
    delete this->windows[this->windowindex];
    this->windows[this->windowindex] = NULL;
    this->windowindex--;

    this->draw();
  }

  if (this->windowindex < 0)
  {
    term->cls();
    term->position(0, 0);
    term->print(F("No window, reboot..."));
    term->flush();

    delay(1500);

    rebootFunc();
  }
}

TerminalWindow* TerminalScreen::getTopWindow()
{
  if (this->windowindex >= 0)
    return this->windows[this->windowindex];
  return NULL;
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
    term->print(this->title);
    term->print(F(" ("));
    term->print(__DATE__);
    term->print(F(")"));

#ifdef DEBUG
    term->print(F(" F: "));
    term->print(String(freeMemory()).c_str());
    term->print(F(" K: "));
    term->print(String(this->key, HEX).c_str());
#endif

    term->position(1, 0);
    for (int i = 0; i < this->title.length() + 14; i++)
      term->print(F("="));

    term->position(2, 0);
    for (byte i = 0; i <= this->windowindex; i++)
    {
      if (i == this->windowindex)
        term->set_attribute(BT_BOLD);

      term->print(this->windows[i]->getTitle());
      if (i < this->windowindex)
        term->print(F(" / "));

      term->set_attribute(BT_NORMAL);
    }

    this->getTopWindow()->draw(term);
  }
}

void TerminalScreen::loop()
{
  this->key = this->term->get_key();
  if (this->key != -1)
    if (this->getTopWindow())
      this->getTopWindow()->processKey(this->key);

  //this->draw();
}
