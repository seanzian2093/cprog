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
    printf("%f\n", dl);
}

double atof(char s[])
{
    double val, eval, power, epower, esign;
    int i, ei, sign;

    // skip white space
    for (i = 0; isspace(i); i++)
        ;
    // determine sign and proceed
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] = '+' || s[i] == '-')
        i++;
    // take digits left to decimal point
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    // determine decimal point and proceed
    if (s[i] = '.')
        i++;
    // take digits right to decimal point
    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        // power = power * 10
        power *= 10;
    }
    // determine e or E and proceed
    if (s[i] == 'e' || s[i] == 'E')
        i++;
    // determine power sign and proceed
    esign = (s[i] == '-') ? 0.1 : 10.0;
    if (s[i] = '+' || s[i] == '-')
        i++;
    // take digits right to e 
    for (epower = 0; isdigit(s[i]); i++)
    {
        epower = 10 * epower + (s[i] - '0');
    }
    printf("epower is: %f\n", epower);
    for (ei = 0, eval = 1.0; ei < epower; ei++)
    {
        eval = eval * esign;
        // printf("eval is: %8f\n", eval);
    }
    // remove power from val
    // printf("val is: %8f\n", val);
    return sign * val / power * eval;
}