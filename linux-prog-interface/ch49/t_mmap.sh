# input '\0', i.e., null bytes to s.txt, each block of size 1, 1024 blocks
dd if=/dev/zero of=s.txt bs=1 count=1024

./t_mmap s.txt hello
./t_mmap s.txt goodbye

od -c -w8 s.txt