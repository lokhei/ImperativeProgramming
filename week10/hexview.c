#include <stdio.h>

int main() {
    FILE *in = fopen("in.txt", "rb");
    int count = 0;

    unsigned char ch = fgetc(in);
    while (! feof(in)) {
        printf("%x ", ch);
        count ++;
        if (count == 16) printf("\n");
        ch = fgetc(in);
    }
    printf("\n");
    fclose(in);
}