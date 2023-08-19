// Concatenate files - 2nd version

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    void filecopy(FILE *, FILE *);
    char *prog = argv[0];
    
    // No args; copy stdin to stdout
    if (argc == 1)
        filecopy(stdin, stdout);
    else
        while(--argc > 0)
            // If error when opening the file
            if ((fp = fopen(*++argv, "r")) == NULL) {
                // fprintf is similar to printf but print to a file, instead stdout
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                // exit calls fclose for each open output files, to fush buffered output
                exit(1);
            }
            else {
                filecopy(fp, stdout);
                fclose(fp);
            }
    // Check error in stdout
    // ferror returns no-zero if an error occured on the stream fp
    if (ferror(stdout)) {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }
    // With main(), return expr is equivalent to exit(expr)
    exit(0);
}

// Copy file ifp to file ofp
void filecopy(FILE *ifp, FILE *ofp)
{
    int c;
    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
}