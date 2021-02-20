#include <stdio.h>
#include <limits.h>
#include <float.h>


int main(){
  printf("Largest int is %d\n", INT_MAX);
  printf("Smallest int is %d\n", INT_MIN);
  printf("Largest character is %d\n", CHAR_MAX);
  printf("Smallest character is %d\n", CHAR_MIN);
  printf("Largest short is %d\n", SHRT_MAX);
  printf("Smallest short is %d\n", SHRT_MIN);
  printf("Largest long is %ld\n", LONG_MAX);
  printf("Smallest long is %ld\n", LONG_MIN);
  printf("Largest float is %f\n", FLT_MAX);
  printf("Smallest float is %f\n", FLT_MIN);
  printf("Largest double is %f\n", DBL_MAX);
  printf("Smallest double is %f\n", DBL_MIN);
  return 0;
}
