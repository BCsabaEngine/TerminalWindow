#include "TerminalWindow.h"

TerminalWindow::TerminalWindow(String title)
{
  this->title = title;
}
TerminalWindow::~TerminalWindow()
{
  for (int i = 0; i < this->runtimecontrolcount; i++)
    delete this->runtimecontrols[i];
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
      this->controls[this->focusedIndex]->focusLeave();
      this->focusedIndex = actual;
      this->controls[this->focusedIndex]->focusEnter();
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
      this->controls[this->focusedIndex]->focusLeave();
      this->focusedIndex = actual;
      this->controls[this->focusedIndex]->focusEnter();
      return;
    }

    actual++;
  }
}

void TerminalWindow::firstFocus()
{
  int actual = 0;

  while (actual < this->controlcount)
  {
    if (this->controls[actual]->canFocus())
    {
      this->controls[this->focusedIndex]->focusLeave();
      this->focusedIndex = actual;
      this->controls[this->focusedIndex]->focusEnter();
      return;
    }

    actual++;
  }
}

void TerminalWindow::lastFocus()
{
  int actual = this->controlcount - 1;

  while (actual >= 0)
  {
    if (this->controls[actual]->canFocus())
    {
      this->controls[this->focusedIndex]->focusLeave();
      this->focusedIndex = actual;
      this->controls[this->focusedIndex]->focusEnter();
      return;
    }

    actual--;
  }
}

void TerminalWindow::dropFocusIfThis(TerminalControl *control)
{
  if (this->focusedIndex >= 0)
    if (this->controls[this->focusedIndex] == control)
      this->nextFocus();
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

void TerminalWindow::addRuntimeControl(TerminalControl *control)
{
  if (this->runtimecontrolcount >= CONTROL_MAX_COUNT)
    return;

  this->addControl(control);

  this->runtimecontrols[this->runtimecontrolcount] = control;
  this->runtimecontrolcount++;
}
void TerminalWindow::addControl(TerminalControl *control)
{
  if (this->controlcount >= CONTROL_MAX_COUNT)
    return;

  control->setWindow(this);

  this->controls[this->controlcount] = control;
  this->controlcount++;
}
