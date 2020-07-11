// memoryFree header
// From http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1213583720/15
// ...written by user "mem".

#ifndef	MEMORY_FREE_H
#define MEMORY_FREE_H

const int MEMORY_START = 0x20004000;
const int MEMORY_END = MEMORY_START + 0x3C000;

int freeMemory();
int freeStackMemory();
int freeHeapMemory();

int stackPointer();
int heapPointer();

#endif
