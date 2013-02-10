#include <unistd.h>
#include <fcntl.h>

static int lock_reg(int fd,int cmd,int type,off_t offset,int whence,off_t len)
{
    struct flock lock;
    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    return (fcntl(fd,cmd,&lock));
}

static pid_t lock_test(int fd,int type,off_t offset,int whence,off_t len)
{
    struct flock lock;

    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    if(fcntl(fd,F_GETLK,&lock) == -1)
    {
        return -1;
    }
    if(lock.l_type = F_UNLCK)
        return 0;
    return lock.l_pid;
}

int read_lock(int fd,off_t offset,int whence,off_t len)
{
    return lock_reg(fd,F_SETLKW,F_RDLCK,offset,whence,len);
}

int read_lock_try(int fd,off_t offset,int whence,off_t len)
{
    return lock_reg(fd,F_SETLK,F_RDLCK,offset,whence,len);
}

int write_lock(int fd,off_t offset,int whence,off_t len)
{
    return lock_reg(fd,F_SETLKW,F_WRLCK,offset,whence,len);
}

int write_lock_try(int fd,off_t offset,int whence,off_t len)
{
    return lock_reg(fd,F_SETLK,F_WRLCK,offset,whence,len);
}

int unlock(int fd,off_t offset, int whence,off_t len)
{
    return lock_reg(fd,F_SETLK,F_UNLCK,offset,whence,len);
}

int is_read_lockable(int fd, off_t offset,int whence,off_t len)
{
    return !lock_test(fd,F_RDLCK,offset,whence,len);
}

int is_write_lockable(int fd, off_t offset,int whence,off_t len)
{
    return !lock_test(fd,F_WRLCK,offset,whence,len);
}
