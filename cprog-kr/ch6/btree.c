// Binary tree data structure for sorting

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100

// The tree node struct - self-refrencial struct
struct tnode {
    char *word;
    int count;
    // Legal for a tnode to contain a pointer to a tnode
    // Illegal to contain an instance of tnode
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
void treeprint(struct tnode *);
int getword(char *, int);
int getch(void);
void ungetch(int);
char *strdup0(char *);

static char buf[BUFSIZE];
static int bufp = 0;

int main(void)
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            // root is either a new tnode with new word
            // or existing tnode with increment in frequency or  updated left or right
            // updating left or right is calling addtree recursively
            root = addtree(root, word);
    treeprint(root);
    return 0;
}

// Add a node with w at or below p
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    // A new word has arrived
    if (p == NULL) {
        // Make a new node
        p = talloc();
        // Copy the word to p.word
        p->word = strdup0(w);
        // Set the count to 1;
        p->count = 1;
        // Set p.left and p.right to NULL
        p->left = p->right= NULL;
    }
    // If the same word has arrived
    else if ((cond = strcmp(w, p->word)) == 0 )
        // Increase count by 1
        p->count++;
    // If the incoming word is less than current word
    else if (cond < 0)
        // recursively call addtree and add it to p.left
        p->left = addtree(p->left, w);
    // If the incoming word is greater than current word
    else 
        // recursively call addtree and add it to p.right
        p->right = addtree(p->right, w);
    // Finally return updated p
    return p;
}

// In-order print of tree p
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }

}

// Declare that malloc returns a pointer to void
struct tnode *talloc(void)
{
    // malloc return a pointer to the initial location of allocated memory
    // Explicitly coerce the return pointer into desired type with a cast to tnode type
    return (struct tnode *) malloc(sizeof(struct tnode));
}

// Make a duplicate of s
char *strdup0(char *s)
{
    char *p;
    
    // malloc returns NULL is no space is available
    p = (char *) malloc(strlen(s)+1);
    if (p != NULL)
        strcpy(p, s);
    // If p is NULL, pass it on
    return p;
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