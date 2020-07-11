#include "MemoryFree.h"

extern "C" char* _sbrk(int incr);

int freeMemory() {
  //return stackPointer() - heapPointer();
  return freeStackMemory() + freeHeapMemory();
}
int freeStackMemory() {
  return 0; //TODO max size defined in startup_gcc.c,
  //Seems to be in heap with fixed size of 8192 * 4 bytes
}
int freeHeapMemory() {
  return MEMORY_END - heapPointer(); //Heap grows to the end of the mem
}

int stackPointer() {
  char top;
  return (int)&top;
}
int heapPointer() {
  return reinterpret_cast<int>(_sbrk(0));
}