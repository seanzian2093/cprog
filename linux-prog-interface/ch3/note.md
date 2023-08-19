# 3.1 System calls

A system call is a controlled entry point in to the kernel, allowing a process to request that the kernel perform
some action on the process's behalf. The syscalls(2) manual page lists the Linux system calls.

`man syscalls`

Three general points - 

* A system call changes the processor state from user mode to kernel mode, so that the CPU can access protected kernel memory.

* The set of system calls is fixed. Each call is identified by a unique number which is normally invisible to programms which identify system calls by name.

* Each system call may have a set of arguments that specifies information to be transfered from user space to kernel space and vice versa.

# 3.2 Library function

# 3.3 The Standard C Library; the GNU C Library(glibc)

To determine the location of libc use ldd against a program, i.e., most program links to libc

`ldd libc_version | grep libc`

In ubuntu 22.04 the location is - 

`/lib/x86_64-linux-gnu/libc.so.6`

Or use the function *gnu_get_libc_version()* in *<gnu-versions.h>* to return version as a string.

# 3.4 Handling Errors from System Calls and Library Functions

## Handling system call errors
When a system call fails, it sets the global integer variable *errno* to a positive value that identifies the specific error. Including the *<errno.h>* header file provides a declaration of *errno*, as well as a set of constants for various error numbers. All of these symbolic names commence with E.
