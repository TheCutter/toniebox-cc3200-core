#ifndef EnhancedThread_h
#define EnhancedThread_h

#include <Thread.h>

class EnhancedThread : public Thread {
  public:
    EnhancedThread(unsigned long _interval = 0)
      : Thread(_interval) { };
    EnhancedThread(ThreadCallbackHandler callbackHandler, unsigned long _interval = 0)
      : Thread(callbackHandler, _interval) { };
    void
      run(void),
      runIfNeeded(void),
      reset(void),
      setRunOnce(bool);
    unsigned long getInterval(void);
  private:
    bool _runOnce;
};

#endif
