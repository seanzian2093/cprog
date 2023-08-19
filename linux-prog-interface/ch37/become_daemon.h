// Header file for become_daemon.c

#ifndef BECOME_DAEMON_H
#define BECOME_DAEMON_H

// Don't chdir("/")
#define BD_NO_CHDIR 01
// Don't close all open files
#define BD_NO_CLOSE_FILES 02
// Don't reopen stdin, stdout, and stderr to /dev/null
#define BD_NO_REOPEN_STD_FDS 04
// Don't do a umask(0)
#define BD_NO_UMASK0 010
// Maxium file descriptors to close if sysconf(_SC_OPEN_MAX) is indeterminate
#define BD_MAX_CLOSE 8192

int becomeDaemon(int flags);
#endif