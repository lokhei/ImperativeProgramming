#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>

enum dataTypes{charType, intType};

/*check if sign is 0 (positive) or 1 (negative)*/
int NegOrPos(int number){
  long shift = sizeof(number)*8-1;
  // shift all bits other than sign bit and compute bitwise AND with 1
  int sign = (number >> shift & 1);
  return sign;
}

/*convert decimal to binary*/
void convBinary(int number, int bits, char *binary){
  for (int i = (bits-2); i >= 0; i --){
    int bit = (number >> i) & 1;
    sprintf(binary, "%s%d", binary, bit);
  }

}

/* Prints sign of number*/
void signPrint(int sign){
  if (sign == 0){
    printf("Sign: 0 (Positive)\n");
  }else printf("Sign: 1 (Negative)\n");
}

void charConvert(char input[]) {
    int num = atoi(input);
    int sign = NegOrPos(num);
    signPrint(sign);
    char binary[8] = "";
    convBinary(num, 8, binary);
    printf("Binary: %s\n",binary);
    printf("Hex: %X\n", num);
}

void intConvert(char input[]) {
    int num = atoi(input);
    int sign = NegOrPos(num);
    signPrint(sign);
    char binary[32] = "";
    convBinary(num, 32, binary);
    printf("Binary: %s\n",binary);
    printf("Hex: %X\n", num);
}

/* check input is a number and that it lies within correct range for char type */
int charCheck(char type[], char input[]) {
  int i = 0;
  int num = atoi(input);
  int length = strlen(input);
  // if number is negative, start with i=1 to miss "-"" sign
  if ((input[0] == '-') && (length > 1)) i = 1;
  // check if input is number
    while (i<length) {
      if (!isdigit(input[i])) {
          return -1;
      }
      i++;
  }
  if ((num < CHAR_MIN) || (num > CHAR_MAX)) return -1;
  return charType;
}

/* check input is a number and that it lies within correct range for int type */
int intCheck(char type[], char input[]) {
  int i = 0;
  long num = atol(input);
  int length = strlen(input);
  // if number is negative, start with i=1 to miss "-"" sign
  if ((input[0] == '-') && (length > 1)) i = 1;
  // check if input is number
  while (i<length) {
      if (!isdigit(input[i])) {
          return -1;
      }
      i++;
  }
  if ((num < INT_MIN) || (num > INT_MAX)) return -1;
  return intType;
}

/*check data type provided in arguments*/
int dataType(char type[], char input[]){
  if (strcmp(type, "char") == 0) return charCheck(type, input);
  else if (strcmp(type, "int") == 0) return intCheck(type, input);
  return -1;
}


/*---------------------------TESTS--------------------------------------*/

//assert function
void assert(int line, bool a) {
    if (a) return;
    printf("The test on line %d fails.\n", line);
    exit(1);
}

// test right value if neg or pos
void testNegOrPos(){
  assert(__LINE__, NegOrPos(7) == 0);
  assert(__LINE__, NegOrPos(100) == 0);
  assert(__LINE__, NegOrPos(-7) == 1);
  assert(__LINE__, NegOrPos(-100) == 1);
}

void testDataType(){
  assert(__LINE__, dataType("char", "7")== 0);
  assert(__LINE__, dataType("char", "-7")== 0);
  assert(__LINE__, dataType("int", "7")== 1);
  assert(__LINE__, dataType("int", "-7")== 1);
  assert(__LINE__, dataType("inpt", "7")== -1);
}


void testCharCheck(){
  assert(__LINE__, charCheck("char", "1") == 0);
  assert(__LINE__, charCheck("char", "-1") == 0);
  assert(__LINE__, charCheck("char", "a") == -1);
  assert(__LINE__, charCheck("char", "ab") == -1);
  assert(__LINE__, charCheck("char", "-") == -1);
  assert(__LINE__, charCheck("char", "/") == -1);
  assert(__LINE__, charCheck("char", "127") == 0);
  assert(__LINE__, charCheck("char", "128") == -1);
  assert(__LINE__, charCheck("char", "-128") == 0);
  assert(__LINE__, charCheck("char", "-129") == -1);
}


void testIntCheck(){
  assert(__LINE__, intCheck("int", "1") == 1);
  assert(__LINE__, intCheck("int", "-1") == 1);
  assert(__LINE__, intCheck("int", "a") == -1);
  assert(__LINE__, intCheck("int", "ab") == -1);
  assert(__LINE__, intCheck("int", "-") == -1);
  assert(__LINE__, intCheck("int", "/") == -1);
  char result[150]; 
  long num = INT_MAX; 
  sprintf(result, "%ld", num);
  assert(__LINE__, intCheck("int", result)==1 );
  sprintf(result, "%ld", num+1);
  assert(__LINE__, intCheck("int", result)==-1 );
  num = INT_MIN;
  sprintf(result, "%ld", num);
  assert(__LINE__, intCheck("int", result)==1 );
  sprintf(result, "%ld", num-1);
  assert(__LINE__, intCheck("int", result)==-1 );
}

//run tests
void test (){
  testNegOrPos();
  testDataType();
  testCharCheck();
  testIntCheck();
  printf("All tests passed\n");
}

/* Run the program or, if there are no arguments, test it */
int main(int argc, char *argv[]){
  setbuf(stdout, NULL);
  if (argc == 1) {
      test();
  }else if (argc == 3) {
    int type = dataType(argv[1], argv[2]);
    if (type == charType) charConvert(argv[2]);
    if (type == intType) intConvert(argv[2]);
    if (type == -1) printf("Error with inputs\n");
  } else {
      fprintf(stderr, "Input a type followed by a number e.g.: ./visualise char 7\n");
      exit(1);
  }
  return 0;
}

