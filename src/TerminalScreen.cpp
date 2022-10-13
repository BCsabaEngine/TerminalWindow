#include "TerminalScreen.h"
#include "TerminalWindow.h"

TerminalScreen::TerminalScreen(String title, String footer)
{
  this->windowindex = -1;
  this->title = title;
  this->footer = footer;

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

  if (this->windowindex < WINDOW_MAX_DEPTH)
  {
    this->windowindex++;
    this->windows[this->windowindex] = window;
  }
  else
    delete window;

  this->redrawScreen();
}

void TerminalScreen::popWindow()
{
  if (this->windowindex > 0)
  {
    delete this->windows[this->windowindex];
    this->windows[this->windowindex] = NULL;
    this->windowindex--;

    this->redrawScreen();
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
    if (this->hasBorder())
    {
      term->position(0, 0);
      for (uint8_t x = 0; x < this->borderWidth; x++)
        term->print(F("-"));

      term->position(this->borderHeight - 1, 0);
      for (uint8_t x = 0; x < this->borderWidth; x++)
        term->print(F("-"));

      if (this->borderVertical)
        for (uint8_t y = 1; y < this->borderHeight - 1; y++)
        {
          term->position(y, 0);
          term->print(F("|"));
          term->position(y, this->borderWidth - 1);
          term->print(F("|"));
        }
    }

    if (this->hasBorder())
      term->position(0, 4);
    else
      term->position(0, 0);
    term->print(this->title);

    if (this->debug)
    {
      String debuginfo = "";
      this->displaydebuginfo(debuginfo);
      if (debuginfo && debuginfo.length())
      {
        term->print(F(" "));
        term->print(debuginfo.c_str());
        term->print(F(" "));
      }
      // term->print(F("K: "));
      // term->print(String(this->key, HEX).c_str());
    }

    if (!this->hasBorder())
    {
      term->position(1, 0);
      for (byte i = 0; i < this->title.length(); i++)
        term->print(F("="));
    }

    if (this->hasBorder())
      if (this->footer && this->footer.length() && this->footer.length() < this->borderWidth)
      {
        term->position(this->borderHeight - 1, this->borderWidth - this->footer.length() - 4 - 1);
        term->print(this->footer);
      }

    if (this->hasBorder())
      term->position(2, 4);
    else
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

    term->position(0, 0);

    term->flush();

    this->lastRedraw = millis();
  }
}

#ifdef WINDOW_LOOP_INTERVAL_MS
uint32_t looplasttime = 0;
#endif
void TerminalScreen::loop()
{
  uint32_t now = millis();

  this->key = this->term->get_key();
  if (this->key != -1)
  {
    if (this->getTopWindow())
      this->getTopWindow()->processKey(this->key);
    if (this->debug)
      this->redrawScreen();

    this->lastKeyPress = now;
  }

#ifdef AUTO_MAINWINDOW_SEC
  if (now - this->lastKeyPress > 1000ULL * AUTO_MAINWINDOW_SEC)
  {
    while (this->windowindex > 0)
      this->popWindow();
    if (this->getTopWindow())
      this->getTopWindow()->firstFocus();
  }
#endif

#ifdef WINDOW_LOOP_INTERVAL_MS
  if (this->getTopWindow())
    if (now - looplasttime > WINDOW_LOOP_INTERVAL_MS)
    {
      this->getTopWindow()->loop();
      looplasttime = now;
    }
#endif

  if (this->needRedraw || now - this->lastRedraw >= SCREEN_REDRAW_MAX_LATENCY_MS)
    if (now - this->lastRedraw >= SCREEN_REDRAW_LATENCY_MS)
    {
      this->draw();
      this->needRedraw = false;
    }
}
