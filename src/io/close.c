#include "nxio/fd.h"
#include "nxio/lk.h"

#include "io.h"

int nxio_close(int fd)
{
    return nxcrt_fd_release(fd);
}