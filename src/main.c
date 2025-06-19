#include <stdio.h>
#include <string.h>
#include "generator.h"
#include "validator.h"
#include "utils.h"

int main() {
    int opcao;

    do {
        printf("\n==== Secure Password CLI ====\n");
        printf("1. Generate Password\n");
        printf("2. Validate Password Strength\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &opcao);
        clearInputBuffer();

        if (opcao == 1) {
            int length, upper, lower, digits, symbols;
            char password[256];

            printf("Enter password length: ");
            scanf("%d", &length);
            clearInputBuffer();

            printf("Use uppercase? (1 = Yes, 0 = No): ");
            scanf("%d", &upper);
            clearInputBuffer();

            printf("Use lowercase? (1 = Yes, 0 = No): ");
            scanf("%d", &lower);
            clearInputBuffer();

            printf("Use digits? (1 = Yes, 0 = No): ");
            scanf("%d", &digits);
            clearInputBuffer();

            printf("Use symbols? (1 = Yes, 0 = No): ");
            scanf("%d", &symbols);
            clearInputBuffer();

            generatePassword(length, upper, lower, digits, symbols, password);
            printf("Generated Password: %s\n", password);

        } else if (opcao == 2) {
            char password[256];
            printf("Enter password to validate: ");
            fgets(password, sizeof(password), stdin);
            password[strcspn(password, "\n")] = 0;
            validatePassword(password);
        }

    } while (opcao != 3);

    printf("Goodbye!\n");
    return 0;
}

