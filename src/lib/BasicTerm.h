/*
   BasicTerm.h
   Provides basic ANSI/VT220 terminal control over a serial interface
   Copyright 2011 Trannie Carter <borys@nottwo.org>
   Licensed for use under the terms of the GNU Lesser General Public License v3
*/

#ifndef BASICTERM_H
#define BASICTERM_H

#include <Arduino.h>

class BasicTerm : public Stream
{

#define BT_NORMAL 0
#define BT_BOLD 1
// #define BT_UNDERLINE 2
// #define BT_BLINK 4
#define BT_REVERSE 8

#define BT_BLACK 0
#define BT_RED 1
#define BT_GREEN 2
#define BT_YELLOW 3
#define BT_BLUE 4
#define BT_MAGENTA 5
#define BT_CYAN 6
#define BT_WHITE 7
  // #define BT_H_YELLOW 11

#define BT_KEY_UNKNOWN 0401
#define BT_KEY_DOWN 0402
#define BT_KEY_UP 0403
#define BT_KEY_LEFT 0404
#define BT_KEY_RIGHT 0405
#define BT_KEY_F0 0410
#define BT_KEY_F(n) (BT_KEY_F0 + (n))

#define BT_ALTCHAR 0x80
#define BT_START_ALTCHAR (F("\x1b(0"))
#define BT_END_ALTCHAR (F("\x1b(B"))
#define BT_ACS(c) (BT_ALTCHAR | (c))
#define BT_ULCORNER BT_ACS('l')
#define BT_LLCORNER BT_ACS('m')
#define BT_URCORNER BT_ACS('k')
#define BT_LRCORNER BT_ACS('j')
#define BT_LTEE BT_ACS('t')
#define BT_RTEE BT_ACS('u')
#define BT_BTEE BT_ACS('v')
#define BT_TTEE BT_ACS('w')
#define BT_HLINE BT_ACS('q')
#define BT_VLINE BT_ACS('x')
#define BT_PLUS BT_ACS('n')
#define BT_S1 BT_ACS('o')
#define BT_S3 BT_ACS('p')
#define BT_S5 BT_ACS('q')
#define BT_S7 BT_ACS('r')
#define BT_S9 BT_ACS('s')
#define BT_DIAMOND BT_ACS('`')
#define BT_CKBOARD BT_ACS('a')
#define BT_DEGREE BT_ACS('f')
#define BT_PLMINUS BT_ACS('g')
#define BT_BULLET BT_ACS('~')
#define BT_LEQUAL BT_ACS('y')
#define BT_GEQUAL BT_ACS('z')
#define BT_NEQUAL BT_ACS('|')
#define BT_POUNDS BT_ACS('}')

private:
  Stream *serial;

public:
  BasicTerm(Stream *ser)
  {
    serial = ser;
  }
  virtual ~BasicTerm() {}

  virtual int available(void)
  {
    return serial->available();
  }

  virtual int peek(void)
  {
    return serial->peek();
  }

  virtual int read(void)
  {
    return serial->read();
  }

  virtual void flush(void)
  {
    serial->flush();
  }

  virtual size_t write(uint8_t c)
  {
    uint8_t ret;

    if (c & BT_ALTCHAR)
    {
      serial->print(BT_START_ALTCHAR);
      ret = serial->write(c & ~BT_ALTCHAR);
      serial->print(BT_END_ALTCHAR);
      return ret;
    }

    return serial->write(c);
  }

  using Print::write;

  void init(void)
  {
    serial->print(F("\x1b\x63"));
  }

  void cls(void)
  {
    serial->print(F("\x1b[2J"));
  }

  void position(uint8_t row, uint8_t col)
  {
    serial->print(F("\x1b["));
    serial->print((uint8_t)row + 1);
    serial->print(F(";"));
    serial->print((uint8_t)col + 1);
    serial->print(F("H"));
  }

  void show_cursor(bool show)
  {
    if (show)
    {
      serial->print(F("\x1b[?25h"));
    }
    else
    {
      serial->print(F("\x1b[?25l"));
    }
  }

  int16_t get_key(void)
  {
    int16_t key;
    uint16_t when;

    key = serial->read();

    if (key == 0x1b)
    { /* escape sequence */
      when = millis();
      while (serial->available() < 2)
      {
        if (((uint16_t)millis() - when) > 250)
        {
          return key;
        }
      }

      key = serial->read();

      switch (key)
      {
      case '[':
        key = serial->read();
        switch (key)
        {
        case 'A':
          return BT_KEY_UP;
        case 'B':
          return BT_KEY_DOWN;
        case 'C':
          return BT_KEY_RIGHT;
        case 'D':
          return BT_KEY_LEFT;
        default:
          return BT_KEY_UNKNOWN;
        }
        break;
      case 'O':
        key = serial->read();
        switch (key)
        {
        case 'P':
          return BT_KEY_F(1);
        case 'Q':
          return BT_KEY_F(2);
        case 'R':
          return BT_KEY_F(3);
        case 'S':
          return BT_KEY_F(4);
        default:
          return BT_KEY_UNKNOWN;
        }
        break;
      default:
        return BT_KEY_UNKNOWN;
      }
    }

    return key;
  }

  void set_attribute(uint8_t attr)
  {
    if (attr & BT_REVERSE)
    {
      serial->print(F("\x1b[7m"));
    }
    if (attr & BT_UNDERLINE)
    {
      serial->print(F("\x1b[4m"));
    }
    if (attr & BT_BOLD)
    {
      serial->print(F("\x1b[1m"));
    }
    if (attr & BT_BLINK)
    {
      serial->print(F("\x1b[5m"));
    }
    if (attr == BT_NORMAL)
    {
      serial->print(F("\x1b[0m"));
    }
  }

  void set_color(uint8_t fg, uint8_t bg)
  {
    serial->print(F("\x1b["));
    serial->print(30 + fg);
    serial->print(F(";"));
    serial->print(40 + bg);
    serial->print(F("m"));
  }

  void set_fg_color(uint8_t fg)
  {
    serial->print(F("\x1b["));
    if (fg < 8)
    {
      serial->print(30 + fg);
    }
    else
    {
      serial->print(F("38;5;"));
      serial->print(fg);
    }
    serial->print(F("m"));
  }

  void set_bg_color(uint8_t bg)
  {
    serial->print(F("\x1b["));
    serial->print(40 + bg);
    serial->print(F("m"));
  }

  void beep(void)
  {
    serial->print(F("\x07"));
  }
};

#endif
