#include <stdio.h>
#include <string.h>
#include "breached.h"

#define MAX_LINE 256

int isPasswordBreached(const char *password) {
    FILE *file = fopen("data/common_passwords.txt", "r");
    if (file == NULL) {
        printf("⚠️  Warning: Could not open breached passwords file.\n");
        return 0;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        // Remove newline
        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, password) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

