		#ifndef __RWLOCK_H__
		#define __RWLOCK_H__

		int read_lock(int fd,off_t offset,int whence,off_t len);
		int read_lock_try(int fd,off_t offset,int whence,off_t len);
		int write_lock(int fd,off_t offset,int whence,off_t len);
		int write_lock_try(int fd,off_t offset,int whence,off_t len);
		int unlock(int fd,off_t offset, int whence,off_t len);
		int is_read_lockable(int fd, off_t offset,int whence,off_t len);
		int is_write_lockable(int fd, off_t offset,int whence,off_t len);

		#endif