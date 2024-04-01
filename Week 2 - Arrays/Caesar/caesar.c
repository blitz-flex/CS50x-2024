#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);

char rotate(char c, int n);

int main(int argc, string argv[])

{
    // argument number
    if (argc != 2 || only_digits(argv[1]) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert argv[1] from a `string` to an `int`
    int k = 0;
    if (argv[1])
    {
        k = atoi(argv[1]);
    }

    // get Prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    // change every char of plaintext
    for (int i = 0, len = strlen(plaintext); i < len; i++)

    {
        printf("%c", rotate(plaintext[i], k));
    }
    printf("\n");

    return 0;
}
// Check the key contains only digits
bool only_digits(string s)
{
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        if (isdigit(s[i]) == 0)
        {
            return false;
        }
    }
    return true;
}
// Rotate the character if it's a letter

char rotate(char c, int n)
{
    if (c >= 'A' && c <= 'Z')
    {
        int index = (c - 'A' + n) % 26;
        return ('A' + index);
    }
    else if (c >= 'a' && c <= 'z')
    {
        int index = (c - 'a' + n) % 26;
        return ('a' + index);
    }
    else
    {
        return c;
    }
}
