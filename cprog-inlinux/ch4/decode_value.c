// C programming in Linux - ch4_2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decode_value(const char *key, char *value, int size)
{
    int length = 0, i = 0, j = 0;
    char *pos1 = '\0', *pos2 = '\0'; 

    // If the key, e.g. ITEM1 is the in query string
    // strstr(cs, ct) return pointer to 1st occurrence of string ct in cs or NULL if not present
    if ((pos1 = strstr((char *) getenv("QUERY_STRING"), key)) != NULL)
    {
        // Move pos1 forward for strlen so pos1 points at the 1st char of value e.g. s in ITEM1=sean
        for (i = 0; i < strlen(key); i++)
            pos1++;
        // pos1 contains & if querystring is like ITEM1=sean&ITEM2=zhang since pos1 points at s
        // so that pos2 points at &
        if ((pos2 = strstr(pos1, "&")) != NULL)
            // so value sean has length pos2 - pos1
            length = pos2 - pos1;
        else
            // Otherwise it is just pos1 length
            length = strlen(pos1);
        
        // Copy char by char from query string to value
        for (i = 0, j = 0; i < length; i++, j++)
        {
            if (j < size)
                value[j] = pos1[i];
        }
        // Add '\0'
        if (j < size)
            value[j] = '\0';
        else
            value[size - 1] = '\0';
    }
}