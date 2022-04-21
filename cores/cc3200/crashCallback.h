#ifndef __CRASH_CALLBACK_H__
#define __CRASH_CALLBACK_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

typedef enum crashSource {
    CRASH_TEST = 0x00,
    CRASH_NMI = 0x01,
    CRASH_FAULT = 0x02,
    CRASH_INT = 0x03,
    CRASH_BUS = 0x04
} crashSource;

typedef void (*crash_callback)(crashSource, uint32_t);
void register_crash_callback(crash_callback callback);
void crashed(crashSource source, uint32_t sp);

#ifdef __cplusplus
}
#endif

#endif //  __CRASH_CALLBACK_H__