#ifndef UTILS_H
#define UTILS_H
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"


void clearInputBuffer();
int readInt(const char *prompt);

void printSplash();

#endif

