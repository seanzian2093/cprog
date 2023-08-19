// Test become_daemon.c

#include "become_daemon.c"

int main(void)
{
    becomeDaemon(1);
    sleep(60);

    return 0;
}