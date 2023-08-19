#include <stdio.h>

const int COUNT = 3;

void chart(int count, int scores[]);

int main(void) {
    int scores[COUNT];

    for (int i = 0; i < COUNT; i++) {
        printf("Please input an integer: ");
        scanf("%d", &scores[i]);
    }

    chart(COUNT, scores);
}

void chart(int count, int scores[]) {
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < scores[i]; j++) {
            printf("#");
        }
        printf("\n");
    }
}
 