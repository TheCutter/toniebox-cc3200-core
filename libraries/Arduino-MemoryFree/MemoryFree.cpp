#include "MemoryFree.h"

extern "C" char* _sbrk(int incr);
extern "C" int getStackPointerFromStartupgcc();

int freeMemory() {
  //return stackPointer() - heapPointer();
  return freeStackMemory() + freeHeapMemory();
}
int freeStackMemory() {
  return MEMORY_STACK_SIZE - (stackPointer()-getStackPointerFromStartupgcc());
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