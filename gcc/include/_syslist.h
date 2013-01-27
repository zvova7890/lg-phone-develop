/* internal use only -- mapping of "system calls" for libraries that lose
   and only provide C names, so that we end up in violation of ANSI */
#ifndef __SYSLIST_H
#define __SYSLIST_H

#ifdef MISSING_SYSCALL_NAMES
#define _close close
#define _execve execve
#define _fcntl fcntl
#define _fork fork
#define _fstat fstat
#define _getpid getpid
#define _gettimeofday gettimeofday
#define _isatty isatty
#define _kill kill
#define _link link
#define _lseek lseek
#define _mkdir mkdir
#define _open open
#define _read read
#define _sbrk sbrk
#define _stat stat
#define _times times
#define _unlink unlink
#define _wait wait
#define _write write
#endif /* MISSING_SYSCALL_NAMES */


ssize_t _write(int fd, const void *buf, size_t len);
pid_t _getpid();
int _unlink(const char *path);
off_t _lseek(int fd, off_t offset, int whence);
ssize_t _read(int fd, void *buf, size_t len);
int _stat(const char *file, struct stat *pstat);
int _mkdir(const char *dir, mode_t mode);
int _open(const char *file, int flags, ...);


#if defined MISSING_SYSCALL_NAMES || !defined HAVE_OPENDIR
/* If the system call interface is missing opendir, readdir, and
   closedir, there is an implementation of these functions in
   libc/posix that is implemented using open, getdents, and close.
   Note, these functions are currently not in the libc/syscalls
   directory.  */
#define _opendir opendir
#define _readdir readdir
#define _closedir closedir
#endif /* MISSING_SYSCALL_NAMES || !HAVE_OPENDIR */

#endif /* !__SYSLIST_H_ */
