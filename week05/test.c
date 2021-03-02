#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>




int main(){
  char s[10], t[10];
  int i = 0;
  printf("enter a string\n");
  scanf("%s", s);
  for (i = 0; s[i] != '\0'; i++){
    t[i] = s[i];
  }
  t[i] = '\0';
  printf("\n%c", t[0]);
  printf("%c", t[1]);
  printf("%c", t[2]);
  printf("%c\n", t[3]);
  return 0;
}
