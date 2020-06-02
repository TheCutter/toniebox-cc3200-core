#include "EnhancedThread.h"

void EnhancedThread::run() {
  Thread::run();
  loop();
  if (_runOnce)
    Thread::enabled = false;
}

void EnhancedThread::runIfNeeded(void) {
  if(Thread::shouldRun())
    Thread::run();
}

void EnhancedThread::reset(void) {
  Thread::enabled = true;
  Thread::runned();
}

void EnhancedThread::setRunOnce(bool runOnce) {
  _runOnce = runOnce;
}
unsigned long EnhancedThread::getInterval(void) {
  return interval;
}
