#ifndef EnhancedThread_h
#define EnhancedThread_h

#include <Thread.h>

class EnhancedThread : public Thread {
  public:
    virtual void loop();
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
