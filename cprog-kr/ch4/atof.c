// Convert string s to double
#include <ctype.h>
#include <stdio.h>

double atof(char s[]);

int main(void)
{
    double dl;
    char s[20];
    scanf("%s", s);
    dl = atof(s);
    printf("%f", dl);
}

double atof(char s[])
{
    double val, power;
    int i, sign;

    // skip white space
    for (i = 0; isspace(i); i++)
        ;
    // determine sign and proceed
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] = '+' || s[i] == '-')
        i++;
    // take digits right to decimal point
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    // determine decimal point and proceed
    if (s[i] = '.')
        i++;
    // take digits left to decimal point
    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        // power = power * 10
        power *= 10;
    }
    // remove power from val
    return sign * val / power;
}