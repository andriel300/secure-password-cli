#include <stdio.h>
#include "utils.h"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int readInt(const char *prompt) {
    char buffer[100];
    int value;

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &value) == 1) {
                return value;
            } else {
                printf("Invalid input. Please enter a number.\n");
            }
        }
    }
}

void printSplash() {
    printf("\033[1;34m"); // Azul brilhante
    printf("\n");
    printf(" ▗▄▄▖▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖▗▄▄▖  ▗▄▖▗▄▄▄▖▗▄▖ ▗▄▄▖ \n");
    printf("▐▌   ▐▌   ▐▛▚▖▐▌▐▌   ▐▌ ▐▌▐▌ ▐▌ █ ▐▌ ▐▌▐▌ ▐▌\n");
    printf("▐▌▝▜▌▐▛▀▀▘▐▌ ▝▜▌▐▛▀▀▘▐▛▀▚▖▐▛▀▜▌ █ ▐▌ ▐▌▐▛▀▚▖\n");
    printf("▝▚▄▞▘▐▙▄▄▖▐▌  ▐▌▐▙▄▄▖▐▌ ▐▌▐▌ ▐▌ █ ▝▚▄▞▘▐▌ ▐▌\n");

    printf("\033[0m"); // Reset cor

    printf("         🔐 Secure Password CLI v2.0\n\n");
}

