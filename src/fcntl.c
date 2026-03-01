#include <stdarg.h>
#include <errno.h>
#include "fcntl.h"
#include "nxio/fd.h"


// Experimental. Not part of MSVC.
int nxio_fcntl(int fd, int cmd, ...)
{
    int result = -1;
    va_list ap;

    if (fd < 0 || fd >= NXCRT_MAX_FDS) {
        errno = EBADF;
        return -1;
    }

    EnterCriticalSection(&nxcrt_fd_table_lock);

    if (!nxcrt_fd_table[fd].used || !nxcrt_fd_table[fd].file) {
        LeaveCriticalSection(&nxcrt_fd_table_lock);
        errno = EBADF;
        return -1;
    }

    nxcrt_fd_t *fde = &nxcrt_fd_table[fd];
    nxcrt_file_t *file = fde->file;

    switch (cmd) {
        case F_DUPFD:
        {
            va_start(ap, cmd);
            int minfd = va_arg(ap, int);
            va_end(ap);

            if (minfd < 0 || minfd >= NXCRT_MAX_FDS) {
                errno = EINVAL;
                break;
            }

            for (int i = minfd; i < NXCRT_MAX_FDS; ++i) {
                if (!nxcrt_fd_table[i].used) {

                    nxcrt_fd_table[i].used = 1;
                    nxcrt_fd_table[i].file = file;
                    nxcrt_fd_table[i].fd_flags = 0;

                    nxcrt_file_lock(file);
                    file->refcount++;
                    nxcrt_file_unlock(file);

                    result = i;
                    break;
                }
            }

            if (result == -1)
                errno = EMFILE;

            break;
        }

        /* Descriptor flags */
        case F_GETFD:
            result = fde->fd_flags;
            break;

        case F_SETFD:
        {
            va_start(ap, cmd);
            int flags = va_arg(ap, int);
            va_end(ap);

            fde->fd_flags = flags;
            result = 0;
            break;
        }

        /* File status flags */
        case F_GETFL:
            nxcrt_file_lock(file);
            result = file->flags;
            nxcrt_file_unlock(file);
            break;

        case F_SETFL:
        {
            va_start(ap, cmd);
            int flags = va_arg(ap, int);
            va_end(ap);

            nxcrt_file_lock(file);

            // FIXME: Only O_APPEND is supported. Expand later.
            file->flags &= ~(O_APPEND);
            file->flags |= (flags & O_APPEND);

            nxcrt_file_unlock(file);

            result = 0;
            break;
        }

        default:
            errno = EINVAL;
            break;
    }

    LeaveCriticalSection(&nxcrt_fd_table_lock);

    return result;
}
