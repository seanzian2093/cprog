// Define two routines that manipulate the names and replacement texts.
#include <stdio.h>
#define HASHSIZE 101

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
// char *strdup(char *);

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        // Self-defined hash function
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

// Put (name, defn) in hashtab
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        // For some reason, np is NULL or copying name fails
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        // Otherwise
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else
        // Free previous np.defn
        free((void *) np->defn);
    
        // Copy defn to np.defn
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    
    // Finally
    return np;
}