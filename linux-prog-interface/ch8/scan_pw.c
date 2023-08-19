// Scan passwd file one by one

#include <pwd.h>
#include "ugid_functions.h"

int main(void)
{
    struct passwd *pwd;

    while((pwd = getpwent()) != NULL)
        printf("%-8s %5ld\n", pwd->pw_name, (long) pwd->pw_uid);

    // Close the passwd file
    endpwent();
}