/* Find the limits of the int type */
#include <stdio.h>
#include <limits.h>

int smallestInt(long low, int high) {
  long mid = high - (high-low)/2; //interval halving
  int test = mid; //tests if mid is in range of int
  if (test==mid) high = mid;
  else low = mid;
  if (high - low < 2) return high;
  return smallestInt(low, high);
}

int main(){
  int n = smallestInt(-2500000000, 0);
  printf("The smallest int is %d\n", n);
  printf("Using limits.h, the smallest int is %d\n", INT_MIN);
  return 0;
}
