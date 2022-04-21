#include "crashCallback.h"

crash_callback crash_callback_ptr;
void register_crash_callback(crash_callback callback) {
    crash_callback_ptr = callback;
}
void crashed(crashSource param) {
    if (crash_callback_ptr)
        (*crash_callback_ptr)(param);                                  
}