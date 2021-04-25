#include "TerminalScreen.h"
#include "TerminalWindow.h"
#ifdef DEBUG
#if defined(ARDUINO_AVR_NANO)
#include <lib/MemoryFree.h>
#endif
#if defined(STM32_CORE_VERSION)
#include <lib/Stm32FreeMem.h>
#endif
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

void TerminalScreen::addWindow(TerminalWindow *window)
{
  window->setScreen(this);

  window->init();

  this->windowindex++;
  this->windows[this->windowindex] = window;

  this->redrawScreen();
}

#if defined(ARDUINO_AVR_NANO)
void (*rebootFunc)(void) = 0;
#endif

#ifdef STM32_CORE_VERSION
void rebootFunc()
{
  NVIC_SystemReset();
}
#endif

void TerminalScreen::popWindow()
{
  if (this->windowindex >= 0)
  {
    delete this->windows[this->windowindex];
    this->windows[this->windowindex] = NULL;
    this->windowindex--;

    this->redrawScreen();
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

TerminalWindow *TerminalScreen::getTopWindow()
{
  if (this->windowindex >= 0)
    return this->windows[this->windowindex];
  return NULL;
}

void TerminalScreen::redrawScreen()
{
  this->needRedraw = true;
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
#if defined(ARDUINO_AVR_NANO)
    term->print(F(" F: "));
    term->print(String(freeMemory()).c_str());
#endif
#if defined(STM32_CORE_VERSION)
    term->print(F(" F: "));
    term->print(String(getStm32FreeMem()).c_str());
#endif
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

      term->print(this->windows[i]->title);
      if (i < this->windowindex)
        term->print(F(" / "));

      term->set_attribute(BT_NORMAL);
    }

    this->getTopWindow()->draw(term);
    
    term->flush();

    this->lastRedraw = millis();
  }
}

void TerminalScreen::loop() {
  this->key = this->term->get_key();
  if (this->key != -1)
  {
    if (this->getTopWindow())
      this->getTopWindow()->processKey(this->key);
#ifdef DEBUG
    this->redrawScreen();
#endif
  }

  unsigned long now = millis();
  if (this->needRedraw || now - this->lastRedraw >= SCREEN_REDRAW_MAX_LATENCY_MS)
    if (now - this->lastRedraw >= SCREEN_REDRAW_LATENCY_MS) {
      this->draw();
      this->needRedraw = false;
    }
}
