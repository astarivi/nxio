#pragma once

#ifdef NXIO_POSIX

    #include <time.h>

    #ifdef __cplusplus
    extern "C" {
    #endif

    struct timeval {
        time_t tv_sec;
        long   tv_usec;
    };

    struct timezone {
        int tz_minuteswest;
        int tz_dsttime;
    };

    int gettimeofday(struct timeval *tv, struct timezone *tz);

    #ifdef __cplusplus
    }
    #endif

#endif // NXIO_POSIX
