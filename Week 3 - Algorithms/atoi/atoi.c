#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // base case
    if (input[0] == '\0')
        return 0;

    // recursia
    int sing = 0;
    while (input[sing] != '\0')
    {
        sing++;
    }
    int last_digit = input[sing - 1] -'0';
    input[sing - 1] = '\0';
    return last_digit + 10 * convert(input);
}
