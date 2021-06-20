#ifndef STM32FREEMEM_H
#define STM32FREEMEM_H

#include <malloc.h>

extern "C" char *sbrk(int i);
/* Use linker definition */
extern char _end;
extern char _sdata;
extern char _estack;
extern char _Min_Stack_Size;

static char *ramstart = &_sdata;
static char *ramend = &_estack;
static char *minSP = (char *)(ramend - &_Min_Stack_Size);

int getStm32FreeMem()
{
  char *heapend = (char *)sbrk(0);
  char *stack_ptr = (char *)__get_MSP();
  struct mallinfo mi = mallinfo();

  /*
  Serial.print("Total non-mmapped bytes (arena):       ");
  Serial.println(mi.arena);
  Serial.print("# of free chunks (ordblks):            ");
  Serial.println(mi.ordblks);
  Serial.print("# of free fastbin blocks (smblks):     ");
  Serial.println(mi.smblks);
  Serial.print("# of mapped regions (hblks):           ");
  Serial.println(mi.hblks);
  Serial.print("Bytes in mapped regions (hblkhd):      ");
  Serial.println(mi.hblkhd);
  Serial.print("Max. total allocated space (usmblks):  ");
  Serial.println(mi.usmblks);
  Serial.print("Free bytes held in fastbins (fsmblks): ");
  Serial.println(mi.fsmblks);
  Serial.print("Total allocated space (uordblks):      ");
  Serial.println(mi.uordblks);
  Serial.print("Total free space (fordblks):           ");
  Serial.println(mi.fordblks);
  Serial.print("Topmost releasable block (keepcost):   ");
  Serial.println(mi.keepcost);

  Serial.print("RAM Start at:       0x");
  Serial.println((unsigned long)ramstart, HEX);
  Serial.print("Data/Bss end at:    0x");
  Serial.println((unsigned long)&_end, HEX);
  Serial.print("Heap end at:        0x");
  Serial.println((unsigned long)heapend, HEX);
  Serial.print("Stack Ptr end at:   0x");
  Serial.println((unsigned long)stack_ptr, HEX);
  Serial.print("RAM End at:         0x");
  Serial.println((unsigned long)ramend, HEX);

  Serial.print("Heap RAM Used:      ");
  Serial.println(mi.uordblks);
  Serial.print("Program RAM Used:   ");
  Serial.println(&_end - ramstart);
  Serial.print("Stack RAM Used:     ");
  Serial.println(ramend - stack_ptr);
  Serial.print("Estimated Free RAM: ");
*/
  return ((stack_ptr < minSP) ? stack_ptr : minSP) - heapend + mi.fordblks;
}
#endif