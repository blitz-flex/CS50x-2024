#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// Complete the Boolean function below
bool valid(string password)
{
    bool checkLower = false;
    bool checkUper = false;
    bool checkNumber = false;
    bool checkSymbol = false;

    for (int i = 0; i < strlen(password); i++)
    {
        if (islower(password[i]))
        {
            checkLower = true;
        }

        if (isupper(password[i]))
        {
            checkUper = true;
        }

        if (isdigit(password[i]))
        {
            checkNumber = true;
        }

        if (!isalnum(password[i]))
        {
            checkSymbol = true;
        }
    }
    if (checkLower == true && checkUper == true && checkNumber == true && checkSymbol == true)
    {
        return true;
    }
    return false;
}
