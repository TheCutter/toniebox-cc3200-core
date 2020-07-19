#ifndef EnhancedThread_h
#define EnhancedThread_h

#include <Thread.h>

class EnhancedThread : public Thread {
  public:
    EnhancedThread(unsigned long _interval = 0)
      : Thread(_interval) { resetStats(); };
    EnhancedThread(ThreadCallbackHandler callbackHandler, unsigned long _interval = 0)
      : Thread(callbackHandler, _interval) { resetStats(); };
    void
      run(void),
      runIfNeeded(void),
      reset(void),
      setRunOnce(bool);
    
    #ifdef USE_THREAD_NAMES
    void setName(const char* name);
    #endif

    unsigned long getInterval(void);

    void resetStats();
    void logStats();
    const static uint8_t STAT_SAMPLES = 10;
    const static uint8_t STAT_SAMPLES_INTERVAL = 10;
    struct LOOP_STATS {
      uint16_t min;
      uint16_t max;
      uint16_t samples[STAT_SAMPLES];
      uint16_t minInterval; 
      uint16_t maxInterval;
      uint16_t samplesInterval[STAT_SAMPLES_INTERVAL];
    };
    LOOP_STATS stats;

  private:
    bool _runOnce;

    bool _firstIntervalSample = true;
};

#endif
