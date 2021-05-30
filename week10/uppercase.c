#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>


int main(int n, char *args[]) {  
     if (n < 3){
        printf("Please provide input and output file path\n");
        return -1;
    }  
    FILE *in = fopen(args[1], "r");
    FILE *out = fopen(args[2], "w");
    char ch = fgetc(in);
    while (! feof(in)) {
        fprintf(out, "%c", toupper(ch));
        ch = getc(in);

    }
    fclose(in);
    fclose(out);
    return 0;

}
