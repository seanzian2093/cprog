// Convert s to integer
#include <ctype.h>
#include <stdio.h>

int atoi(char s[]);

int main(void)
{
    int ret;
    char s[10];
    scanf("%s", s);
    ret = atoi(s);
    printf("%d\n", ret);
}

int atoi(char s[])
{
    int i, n, sign;
    //skip white space
    for (i = 0; isspace(s[i]); i++)
        ;
    //skip sign
    sign = (s[i] == '-') ? -1 : 1;//ternary expression
    if (s[i] == '+' || s[i] == '-')
        i++;
    // use digit
    for (n = 0; isdigit(s[i]); i++)
        n = n * 10 + (s[i] - '0');
    
    return sign * n;
}