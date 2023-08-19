// Count C keywords using pointers instead of array indices

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
// #define NKEYS (size of keytab / sizeof(strcut key))
// equivalently but more robust
#define NKEYS (sizeof keytab / sizeof(keytab[0]))
#define BUFSIZE 100

// Define and initialize keytab, an array of key which is a struct with member word and count
struct key {
    char *word;
    int count;
} keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"unsigned", 0},
    {"void", 0}
};

static char buf[BUFSIZE];
static int bufp = 0;
int getch(void);
void ungetch(int);
int getword(char *, int);
struct key *binsearch(char *, struct key *, int);

int main(void)
{
    char word[MAXWORD];
    struct key *p;

    while (getword(word, MAXWORD) != EOF)
    {
        if (isalpha(word[0]))
            if ((p = binsearch(word, keytab, NKEYS)) != NULL)
                p->count++;
    }

    // After EOF is inputted, print outk content of keytab
    // unit of pointer arithmetic is one element of underlying object
    for (p = keytab; p < keytab + NKEYS; p++)
        if (p->count > 0)
            printf("%4d %s\n", p->count, p->word);
    
    return 0;
}

// Find word in tab[0],...,tab[n-1]
struct key *binsearch(char * word, struct key *tab, int n)
{
    int cond;
    struct key *low = &tab[0];
    struct key *high = &tab[n];
    struct key *mid;
    while (low < high)
    {
        // pointer addition is iilegal
        // substrction is legal but result is the number of elements
        mid = low + (high-low) / 2;
        if ((cond = strcmp(word, mid->word)) < 0)
            high = mid;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return NULL;
}

// Get next word or character from input
int getword(char *word, int lim)
{
    int c;
    // int c, getch(void);
    // void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c))
    {
        *w = '\0';
        return c;
    }

    for (; --lim >0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

// Get a (possibly pushed-back) character
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

// Push character back on input
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}