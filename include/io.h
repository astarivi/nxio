#pragma once

#include <stdio.h> // SEEK_

#include "sys/types.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef F_OK
#define F_OK 0
#endif

#ifndef X_OK
#define X_OK 1
#endif

#ifndef W_OK
#define W_OK 2
#endif

#ifndef R_OK
#define R_OK 4
#endif

int nxio_open(const char *path, int oflag, ...);
int nxio_sopen(const char *path, int oflag, int shflag, ...);
int nxio_unlink(const char *path);
int nxio_close(int fd);
int nxio_dup(int fd);
int nxio_dup2(int oldfd, int newfd);
int nxio_access(const char *path, int amode);

#ifdef NXIO_POSIX

    off_t nxio_lseek(int fd, off_t offset, int whence);

    ssize_t nxio_read_posix(int fd, void *buf, size_t cnt);

    ssize_t nxio_write_posix(int fd, void *buf, size_t cnt);

    #define lseek nxio_lseek

    #define open nxio_open
    #define sopen nxio_sopen
    #define read nxio_read_posix
    #define unlink nxio_unlink
    #define close nxio_close
    #define dup nxio_dup
    #define dup2 nxio_dup2
    #define write nxio_write_posix
    #define access nxio_access

#else // NXIO_POSIX

    long nxio_lseek32(int fd, long offset, int whence);
    int64_t nxio_lseeki64(int fd, int64_t offset, int whence);

    int nxio_read32(int fd, void *buf, unsigned int cnt);

    int nxio_write32(int fd, void *buf, unsigned int cnt);

    #define _lseek nxio_lseek32
    #define _lseeki64 nxio_lseeki64

    #define _open nxio_open
    #define _sopen nxio_sopen

    #define _read nxio_read32

    #define _unlink nxio_unlink

    #define _close nxio_close

    #define _dup nxio_dup
    #define _dup2 nxio_dup2

    #define _write nxio_write32

    #define _access nxio_access

#endif // NXIO_POSIX

#ifdef __cplusplus
}
#endif
