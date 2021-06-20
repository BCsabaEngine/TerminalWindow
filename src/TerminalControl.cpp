#include "TerminalConfig.h"
#include "TerminalScreen.h"
#include "TerminalControl.h"

void TerminalControl::redrawScreen()
{
  if (this->window)
    this->window->redrawScreen();
}

String TerminalControl::shortString(String s)
{
  if (s.length() > this->width)
    return s.substring(0, this->width);
  return s;
}

TerminalControl::TerminalControl(byte x, byte y, byte width)
{
  this->x = x;
  this->y = y + SCREEN_HEADER_LINES + WINDOW_ROUTE_LINES;
  this->width = width;
}

bool TerminalControl::getVisible() { return this->visible; }

void TerminalControl::setVisible(bool visible)
{
  this->visible = visible;
  if (this->window)
    this->window->lostFocus(this);
  this->redrawScreen();
}

void TerminalControl::addLabel(String text, LabelPos pos)
{
  this->labelText = text;
  this->labelPos = pos;
}

void TerminalControl::labelDraw(BasicTerm *term)
{
  if (!this->labelText || this->labelText.length() == 0)
    return;

  byte x, y;
  String text = this->labelText;
  switch (this->labelPos)
  {
  case labelPosTop:
    x = this->x;
    y = this->y - 1;
    break;
  case labelPosLeft:
    if (text.length() > this->x)
    {
      text = text.substring(text.length() - this->x);
      x = 0;
    }
    else
      x = this->x - text.length();
    y = this->y;
    break;
  }

  term->position(y, x);
  term->print(text);
}

TerminalWindow *TerminalControl::getWindow() { return this->window; }

TerminalScreen *TerminalControl::getScreen() { return this->window->getScreen(); }

void TerminalControl::closeWindow()
{
  if (this->getWindow())
    this->getWindow()->close();
}

void TerminalControl::addWindow(TerminalWindow *window)
{
  if (this->getWindow() && this->getWindow()->getScreen())
    this->getWindow()->getScreen()->addWindow(window);
}

void TerminalControl::setWindow(TerminalWindow *window) { this->window = window; }
