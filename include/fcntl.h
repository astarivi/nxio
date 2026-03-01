#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define O_RDONLY    0x0000
#define O_WRONLY    0x0001
#define O_RDWR      0x0002
#define O_ACCMODE   0x0003

#define O_CREAT     0x0100
#define O_EXCL      0x0200
#define O_TRUNC     0x0400
#define O_APPEND    0x0800

#define O_NONBLOCK  0x1000
#define O_SYNC      0x2000

#define O_BINARY 0
#define O_TEXT   0

#define F_DUPFD    0
#define F_GETFD    1
#define F_SETFD    2
#define F_GETFL    3
#define F_SETFL    4

#define SH_COMPAT   0x00
#define SH_DENYRW   0x10
#define SH_DENYWR   0x20
#define SH_DENYRD   0x30
#define SH_DENYNO   0x40

#define _O_RANDOM       0x0010
#define _O_SEQUENTIAL   0x0020
#define _O_TEMPORARY    0x0040

#ifdef NXIO_POSIX
#define O_TEMPORARY _O_TEMPORARY
#define O_SEQUENTIAL _O_SEQUENTIAL
#define O_RANDOM _O_RANDOM
#endif

int nxio_fcntl(int fd, int cmd, ...);

#ifdef __cplusplus
}
#endif
