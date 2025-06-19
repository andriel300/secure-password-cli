#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "validator.h"

void validatePassword(const char *password) {
    int length = strlen(password);
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSymbol = 0;

    for (int i = 0; i < length; i++) {
        if (isupper(password[i])) hasUpper = 1;
        else if (islower(password[i])) hasLower = 1;
        else if (isdigit(password[i])) hasDigit = 1;
        else hasSymbol = 1;
    }

    printf("\nPassword Analysis:\n");
    printf("- Length: %d\n", length);
    printf("- Uppercase: %s\n", hasUpper ? "Yes" : "No");
    printf("- Lowercase: %s\n", hasLower ? "Yes" : "No");
    printf("- Digits: %s\n", hasDigit ? "Yes" : "No");
    printf("- Symbols: %s\n", hasSymbol ? "Yes" : "No");

    int score = hasUpper + hasLower + hasDigit + hasSymbol;

    if (length >= 12 && score >= 3) {
        printf("✔️ Password Strength: STRONG\n");
    } else if (length >= 8 && score >= 2) {
        printf("✔️ Password Strength: MEDIUM\n");
    } else {
        printf("❌ Password Strength: WEAK\n");
    }
}

