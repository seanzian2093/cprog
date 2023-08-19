# 4.1 Overview

* All system calls for performing I/O refer to open files using a *file descriptor*, a small non-negative integer.

* File descriptors are used to refer to all types of open files, including pipes,FIFOs, sockets, terminals, devices, regular files.
* Each process has its own set of file descriptors.

* Create symbolic link to /usr/include

    * -f to overwrite existing destination
    * -s for symbolic link

`sudo ln -f -s $(pwd)/tlpi_hdr.h /usr/include/tlpi_hdr.h`

Or simply 
`sudo ln -f -s $(pwd)/tlpi_hdr.h /usr/include/`