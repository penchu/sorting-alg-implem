#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>

int rec_func(int n);

int main(void) {
    int n = 10;
    int m = rec_func(n);
    printf("%d\n", m);
}

int rec_func(int n) {
    if (n <= 1) return n;

    rec_func(n-1);
}