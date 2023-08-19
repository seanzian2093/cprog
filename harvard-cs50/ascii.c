// cast char to int

#include <stdio.h>
#include <string.h>

char mystr[10];
int main(void) {
    printf("Please input your string:");
    scanf("%s", &mystr);
    printf("Input: %s\nOutput: \n", mystr);
    int n = strlen(mystr); 
    printf("Length of your input is %d\n", n);

    for (int i = 0; i < n; i++) {
        // cast mystr[i] to int
        int c = (int) mystr[i];
        printf("%c -> %i\n", mystr[i], c);
    }

}