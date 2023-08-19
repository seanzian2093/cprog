// C programming in Linux - ch4_1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    printf("Content-type:text/html\n\n<html><body bgcolor=#23abe2>\n");
    char value[256] = "";
    // printf("QUERY_STRING: %s\n", getenv("QUERY_STRING"));
    // Copy to value at most 255 characters from getenv()
    if ((char *)getenv("QUERY_STRING") == NULL)
        {
            value[0] = 'n';
            value[1] = '\0';
        }
    else
        strncpy(value, (char *)getenv("QUERY_STRING"), 255);
    printf("QUERY_STRING: %s<BR>\n", value);
    printf("<form>\n");
    // To print ", use \ to escape it
    printf("<input type=\"TEXT\" name=\"ITEM1\">\n");
    printf("<input type=\"TEXT\" name=\"ITEM2\">\n");
    printf("<input type=\"SUBMIT\">");
    printf("</form></body></html>\n");

    return 0;
}