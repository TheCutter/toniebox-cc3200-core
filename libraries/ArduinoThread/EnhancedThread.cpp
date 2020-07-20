#include "EnhancedThread.h"
#include "Logging.h"

void EnhancedThread::run() {
  unsigned long before_run = millis();
  unsigned long before_last_run = last_run;
  Thread::run();
  if (_runOnce)
    Thread::enabled = false;
  unsigned long after_run = millis();
  
  unsigned long runtime = after_run - before_run;
  if (runtime < stats.min)
    stats.min = runtime;
  if (runtime > stats.max)
    stats.max = runtime;
  memmove(&stats.samples[1], &stats.samples[0], (STAT_SAMPLES-1)*2);
  stats.samples[0] = runtime;

  if (!_firstIntervalSample) {
    unsigned long calcInterval = before_run - before_last_run;
    if (calcInterval < stats.minInterval)
      stats.minInterval = calcInterval;
    if (calcInterval > stats.maxInterval)
      stats.maxInterval = calcInterval;
    memmove(&stats.samplesInterval[1], &stats.samplesInterval[0], (STAT_SAMPLES_INTERVAL-1)*2);
    stats.samplesInterval[0] = calcInterval;
  } else {
    _firstIntervalSample = false;
  }
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

  stats.minInterval = UINT16_MAX;
  stats.maxInterval = 0;
  for (uint8_t i=0; i<STAT_SAMPLES_INTERVAL; i++)
    stats.samplesInterval[i] = 0;
}
void EnhancedThread::logStats() {
  #ifdef USE_THREAD_NAMES
  Log.info("Thread statistics for %s, priority=%i, interval=%i", ThreadName, priority, interval);
  #else
  Log.info("Thread statistics for %i, priority=%i, interval=%i", ThreadID, priority, interval);
  #endif
  Log.info(" #Measured runtime#");
  Log.info("  Min. %ims", stats.min);
  Log.info("  Max. %ims", stats.max);
  Log.disableNewline(true);
  Log.info("  Samples: ");
  for (uint8_t i=0; i<STAT_SAMPLES; i++) {
    Log.printf(" [%i] %ims,", i, stats.samples[i]);
  }
  Log.disableNewline(false);
  Log.println();
  Log.info(" #Measured interval#");
  Log.info("  Min. %ims", stats.minInterval);
  Log.info("  Max. %ims", stats.maxInterval);
  Log.disableNewline(true);
  Log.info("  Samples:");
  for (uint8_t i=0; i<STAT_SAMPLES_INTERVAL; i++) {
    Log.printf(" [%i] %ims,", i, stats.samplesInterval[i]);
  }
  Log.disableNewline(false);
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
