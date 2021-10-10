#include "TerminalConfig.h"
#include "TerminalLabelMultiLine.h"

TerminalLabelMultiLine::TerminalLabelMultiLine(byte x, byte y, byte width, byte height, uint8_t color) : TerminalControl(x, y, width)
{
  if (height > CONTROL_LABELML_MAX_HEIGHT)
    height = CONTROL_LABELML_MAX_HEIGHT;
  this->height = height;
  this->clearLines();
  this->setColor(color);
}

void TerminalLabelMultiLine::clearLines()
{
  this->linecount = 0;
  this->redrawScreen();
}

void TerminalLabelMultiLine::setLines(String lines[], int linecount)
{
  if (linecount > CONTROL_LABELML_MAX_HEIGHT)
    linecount = CONTROL_LABELML_MAX_HEIGHT;
  if (linecount > this->height)
    linecount = this->height;
  this->linecount = linecount;
  for (int i = 0; i < linecount; i++)
    this->lines[i] = lines[i];
  this->redrawScreen();
}

void TerminalLabelMultiLine::setColor(uint8_t color)
{
  this->color = color;
  this->redrawScreen();
}

void TerminalLabelMultiLine::draw(BasicTerm *term, bool focused)
{
  if (!this->visible)
    return;

  this->labelDraw(term);

  if (focused)
    term->set_attribute(BT_NORMAL);
  term->set_attribute(BT_NORMAL);

  term->set_fg_color(this->color);
  for (byte i = 0; i < this->linecount; i++)
  {
    term->position(this->y + i, this->x);
    term->print(this->lines[i]);
    if (i >= this->height)
      break;
  }
  term->set_fg_color(BT_WHITE);
}
