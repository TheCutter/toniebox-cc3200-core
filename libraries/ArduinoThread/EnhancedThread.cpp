#include "EnhancedThread.h"
#include "Logging.h"

void EnhancedThread::run() {
  unsigned long before_run = millis();
  Thread::run();
  if (_runOnce)
    Thread::enabled = false;
  unsigned long delta = millis() - before_run;
  
  if (delta < stats.min)
    stats.min = delta;
  if (delta > stats.max)
    stats.max = delta;
  memmove(&stats.samples[1], &stats.samples[0], (STAT_SAMPLES-1)*2);
  stats.samples[0] = delta;
  
}

void EnhancedThread::runIfNeeded(void) {
  if(Thread::shouldRun())
    Thread::run();
}

void EnhancedThread:: resetStats() {
  stats.min = UINT16_MAX;
  stats.max = 0;
  for (uint8_t i=0; i<STAT_SAMPLES; i++)
    stats.samples[i] = 0;
}
void EnhancedThread::logStats() {
  #ifdef USE_THREAD_NAMES
  Log.info("Thread statistics for %s", ThreadName);
  #else
  Log.info("Thread statistics for %i", ThreadID);
  #endif
  Log.info(" Inverval %ims", interval);
  Log.info(" Min. %ims", stats.min);
  Log.info(" Max. %ims", stats.max);
  Log.info(" Samples:");
  for (uint8_t i=0; i<STAT_SAMPLES; i++) {
    //if (stats.samples[i] == 0)
    //  break;
    Log.printf("[%i] %ims, ", i, stats.samples[i]);
  }
  Log.println();
}

#ifdef USE_THREAD_NAMES
void EnhancedThread::setName(const char* name) {
  sprintf(ThreadName, "%s (0x%X)", name, ThreadID);
}
#endif

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
