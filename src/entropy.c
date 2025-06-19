#include <stdio.h>
#include <math.h>
#include "entropy.h"
#include "utils.h"

double calculateEntropy(int poolSize, int length) {
    return length * log2(poolSize);
}

void printEntropy(double entropy) {
    printf("\n🔢 Entropy: %.2f bits\n", entropy);

    if (entropy < 28) {
        printf(RED "❌ Very Weak (Instantly Crackable)\n" RESET);
    } else if (entropy < 35) {
        printf(RED "❌ Weak (Few seconds)\n" RESET);
    } else if (entropy < 59) {
        printf(YELLOW "⚠️ Moderate (Few hours or days)\n" RESET);
    } else if (entropy < 127) {
        printf(GREEN "✔️ Strong (Thousands of years)\n" RESET);
    } else {
        printf(GREEN "✔️ Very Strong (Millions of years)\n" RESET);
    }
}

