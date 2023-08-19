// Print string char by char

#include <stdio.h>
#include <string.h>

char mystr[10];
int main(void) {
    printf("Please input your string:");
    // either way is working because array is essentially a pointer already
    // scanf("%s", &mystr);
    scanf("%s", mystr);
    printf("Input: %s\nOutput: \n", mystr);
    int n = strlen(mystr); 
    printf("Length of your input is %d\n", n);

    for (int i = 0; i < n; i++) {
        printf("%c\n", mystr[i]);
    }

}