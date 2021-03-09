#include "TerminalConfig.h"
#include "TerminalScreen.h"
#include "TerminalControl.h"

void TerminalControl::redrawScreen() {
  if (this->window)
    this->window->redrawScreen();
}

String TerminalControl::shortString(String s) {
  if (s.length() > this->width)
    return s.substring(this->width);
  return s;
}

TerminalControl::TerminalControl(byte x, byte y, byte width) {
  this->x = x;
  this->y = y + SCREEN_HEADER_LINES + WINDOW_ROUTE_LINES;
  this->width = width;
}

void TerminalControl::addLabel(String text, LabelPos pos) {
  this->label.text = text;
  this->label.pos = pos;
}

TerminalWindow* TerminalControl::getWindow() {
  return this->window;
}

void TerminalControl::setWindow(TerminalWindow* window) {
  this->window = window;
}
