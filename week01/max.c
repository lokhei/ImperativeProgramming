/* Find the limits of the int type */
#include <stdio.h>
#include <limits.h>

int largestInt(int low, long high) {
  long mid = low + (high-low)/2; //interval halving
  int test = mid; //tests if mid is in range of int
  if (test==mid) low = mid;
  else high = mid;
  if (high - low < 2) return test;
  return largestInt(low, high);
}

int main(){
  int n = largestInt(0,2500000000);
  printf("The largest int is %d\n", n);
  printf("Using limits.h, the largest int is %d\n", INT_MAX);
  return 0;
}
