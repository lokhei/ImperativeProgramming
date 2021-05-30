#include <stdio.h>

int main(int n, char *args[]) {
    if (n != 2){
        printf("Please provide file path\n");
        return -1;
    }
    FILE *in = fopen(args[1], "rb");
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
