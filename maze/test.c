#include <stdio.h>

int main(){
  int k = 137;
  int * p = &k;
  printf("k is stored at %p\n", p);
  return 0;
}
