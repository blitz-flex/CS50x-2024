#include <cs50.h>
#include <stdio.h>

float half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// Complete the function
float half(float bill, float tax, int tip)
{
    // Bill + Tax + Tip
    float amount = bill + (bill * (tax / 100));
    amount += amount * ((float) tip / 100);
    return amount / 2;
}
