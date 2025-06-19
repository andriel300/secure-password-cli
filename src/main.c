#include <stdio.h>
#include <string.h>
#include "generator.h"
#include "validator.h"
#include "utils.h"
#include "entropy.h"
#include "breached.h"

int main() {
    printSplash();
    int opcao;

    do {
        printf("\n==== Secure Password CLI ====\n");
        printf("1. Generate Password\n");
        printf("2. Exit\n");
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
            printf("\nGenerated Password: %s\n", password);

            // Análise da senha gerada
            validatePassword(password);

            // Verificar se a senha foi vazada
            if (isPasswordBreached(password)) {
                printf(RED "❌ This password appears in breached password databases!\n" RESET);
            } else {
                printf(GREEN "✔️ This password was not found in breach lists.\n" RESET);
            }

            // Calcular entropia
            int poolSize = 0;
            if (upper) poolSize += 26;
            if (lower) poolSize += 26;
            if (digits) poolSize += 10;
            if (symbols) poolSize += 32;

            double entropy = calculateEntropy(poolSize, length);
            printEntropy(entropy);
        }

    } while (opcao != 2);

    printf("Goodbye!\n");
    return 0;
}

