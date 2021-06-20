#include "TerminalWindow.h"

TerminalWindow::TerminalWindow(String title)
{
  this->title = title;
}

void TerminalWindow::draw(BasicTerm *term)
{
  for (int i = 0; i < this->controlcount; i++)
    this->controls[i]->draw(term, this->focusedIndex == i);
}

void TerminalWindow::close()
{
  if (this->screen)
    this->screen->popWindow();
}

void TerminalWindow::init()
{
  if (this->focusedIndex == -1)
    for (int i = 0; i < this->controlcount; i++)
      if (this->controls[i]->canFocus())
      {
        this->focusedIndex = i;
        break;
      }
}

void TerminalWindow::redrawScreen()
{
  if (this->screen)
    this->screen->redrawScreen();
}

void TerminalWindow::prevFocus()
{
  int actual = this->focusedIndex - 1;

  while (actual != this->focusedIndex)
  {
    if (actual < 0)
      actual = this->controlcount - 1;

    if (this->controls[actual]->canFocus())
    {
      this->focusedIndex = actual;
      return;
    }

    actual--;
  }
}

void TerminalWindow::nextFocus()
{
  int actual = this->focusedIndex + 1;

  while (actual != this->focusedIndex)
  {
    if (actual >= this->controlcount)
      actual = 0;

    if (this->controls[actual]->canFocus())
    {
      this->focusedIndex = actual;
      return;
    }

    actual++;
  }
}

void TerminalWindow::processKey(uint16_t key)
{

#ifdef WINDOW_CLOSE_ESC
  if (key == 0x1b)
  {
    this->close();
    return;
  }
#endif

  if (this->focusedIndex < 0)
    return;

  bool handled = this->controls[this->focusedIndex]->handleKey(key);
  if (!handled)
    switch (key)
    {

#ifdef CONTROL_MOVE_TAB
    case 0x9:
      this->nextFocus();
      this->redrawScreen();
      break;
#endif

#ifdef CONTROL_MOVE_UP_DOWN
    case BT_KEY_DOWN:
      this->nextFocus();
      this->redrawScreen();
      break;
#endif

#ifdef CONTROL_MOVE_LEFT_RIGHT
    case BT_KEY_RIGHT:
      this->nextFocus();
      this->redrawScreen();
      break;
#endif

#ifdef CONTROL_MOVE_UP_DOWN
    case BT_KEY_UP:
      this->prevFocus();
      this->redrawScreen();
      break;
#endif

#ifdef CONTROL_MOVE_LEFT_RIGHT
    case BT_KEY_LEFT:
      this->prevFocus();
      this->redrawScreen();
      break;
#endif
    }
}

TerminalScreen *TerminalWindow::getScreen()
{
  return this->screen;
}

void TerminalWindow::setScreen(TerminalScreen *screen)
{
  this->screen = screen;
}

void TerminalWindow::addControl(TerminalControl *control)
{
  if (this->controlcount >= CONTROL_MAX_COUNT)
    return;

  control->setWindow(this);

  this->controls[this->controlcount] = control;
  this->controlcount++;
}
