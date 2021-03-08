#include "TerminalConfig.h"
#include "TerminalScreen.h"
#include "TerminalControl.h"

TerminalControl::TerminalControl(int x, int y, int width)
{
  this->x = x;
  this->y = y + SCREEN_HEADER_LINES + WINDOW_ROUTE_LINES;
  this->width = width;
}

TerminalWindow* TerminalControl::getWindow()
{
  return this->window;
}

void TerminalControl::setWindow(TerminalWindow* window)
{
  this->window = window;
}
