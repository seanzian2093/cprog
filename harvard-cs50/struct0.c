// Demonstrates structs
#include <stdio.h>
#include <string.h>
#include "struct.h"

int main(void) {
    // Allocate space for students
    int enrollment;
    printf("Please input an integer: ");
    scanf("%d", &enrollment);
    student students[enrollment];

    // Prompt for students' names and dorms
    for (int i = 0; i <= enrollment; i++) {
        printf("Please input a name: ");
        scanf("%s", students[i].name);
        printf("Please input a dorm: ");
        scanf("%s", students[i].dorm);
    }

    // Print for students' names and dorms
    for (int i = 0; i <= enrollment; i++) {
        printf("Name #%d: %s\n", i, students[i].name);
        printf("Dorm #%d: %s\n", i, students[i].dorm);
    }
}