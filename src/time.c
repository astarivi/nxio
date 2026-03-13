#include "sys/time.h"

#include <xboxkrnl/xboxkrnl.h>
#include <stdint.h>
#include <time.h>

#include "errno.h"

#define NT_EPOCH_TIME_OFFSET ((LONGLONG)(369 * 365 + 89) * 24 * 3600)

#ifdef NXIO_POSIX
int gettimeofday(struct timeval *tv, struct timezone *tz)
{
    if (!tv) {
        errno = EINVAL;
        return -1;
    }

    LARGE_INTEGER cur_time;
    KeQuerySystemTime(&cur_time);

    uint64_t total_100ns = (uint64_t)cur_time.QuadPart;

    uint64_t total_sec  = total_100ns / 10000000ULL;
    uint64_t total_usec = (total_100ns % 10000000ULL) / 10ULL;

    tv->tv_sec  = (time_t)(total_sec - NT_EPOCH_TIME_OFFSET);
    tv->tv_usec = (long)total_usec;

    if (tz) {
        tz->tz_minuteswest = 0;
        tz->tz_dsttime = 0;
    }

    return 0;
}
#endif
