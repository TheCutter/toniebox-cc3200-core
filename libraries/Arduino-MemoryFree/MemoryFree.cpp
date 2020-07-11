#include "MemoryFree.h"

extern "C" char* _sbrk(int incr);

int freeMemory() {
  char top;
  return stackPointer() - heapPointer();
}
int stackPointer() {
  char top;
  return (int)&top;
}
int heapPointer() {
  return reinterpret_cast<int>(_sbrk(0));
}