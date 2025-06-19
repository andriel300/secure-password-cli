#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "generator.h"

void generatePassword(int length, int useUpper, int useLower, int useDigits, int useSymbols, char *output) {
    const char *upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *lower = "abcdefghijklmnopqrstuvwxyz";
    const char *digits = "0123456789";
    const char *symbols = "!@#$%^&*()_+-=[]{}|;:,.<>?";

    char pool[256] = "";
    if (useUpper) strcat(pool, upper);
    if (useLower) strcat(pool, lower);
    if (useDigits) strcat(pool, digits);
    if (useSymbols) strcat(pool, symbols);

    if (strlen(pool) == 0) {
        printf("Error: No character sets selected.\n");
        strcpy(output, "");
        return;
    }

    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        output[i] = pool[rand() % strlen(pool)];
    }
    output[length] = '\0';
}

