// Concatenate files - 1st version

#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    void filecopy(FILE *, FILE *);
    
    // No args; copy stdin to stdout
    if (argc == 1)
        filecopy(stdin, stdout);
    else
        while(--argc > 0)
            // If error when opening the file
            if ((fp = fopen(*++argv, "r")) == NULL) {
                printf("cat: can't open %s\n", *argv);
                return 1;
            }
            else {
                filecopy(fp, stdout);
                fclose(fp);
            }
    return 0;
}

// Copy file ifp to file ofp
void filecopy(FILE *ifp, FILE *ofp)
{
    int c;
    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
}