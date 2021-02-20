/* Calculate interest. */
#include <stdio.h>

double add(double amount, double interestRate) {
  double new_amount = amount * (1+(interestRate/100));
  return new_amount;
}

int main() {
    double amount , interestRate;
    printf("Enter the amount of savings: ");
    scanf("%lf", &amount);
    printf("\nEnter the Interest Rate(%%): ");
    scanf("%lf", &interestRate);
    double new_amount = add(amount, interestRate);
    printf("Adding %.2lf%% interest to %.2lf gives %.2lf\n", interestRate, amount, new_amount);
    return 0;
}
