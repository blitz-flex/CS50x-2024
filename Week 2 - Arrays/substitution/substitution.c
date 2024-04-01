#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool key(string s);

char cout_letter(char letter, string s);

int main(int argc, string argv[])

{
    // argument number
    if (argc != 2)
    {
        printf("Usage: ./Substitution key\n");
        return 1;
    }

    // Check the key is valid or not
    if (argv[1])
    {
        if (key(argv[1]) == 0)
            return 1;
    }
    // get prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    // each letter and  ciphertext
    printf("ciphertext: ");

    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        printf("%c", cout_letter(plaintext[i], argv[1]));
    }
    printf("\n");
    return 0;
}

bool key(string s)
{
    // check key lenght
    if (strlen(s) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 0;
    }

    // check non-aphabetic characters

    for (int i = 0; i < 26; i++)
    {
        if (isalpha(s[i]) == 0)
        {
            printf("The key must consist of only letters of the alphabet.\n");
            return 0;
        }
    }

    // Check for repetad chracters(case-insensitive)

    int char_count[26] = {0};
    for (int i = 0; i < 26; i++)
    {
        char lowercase_char = tolower(s[i]);

        if (lowercase_char >= 'a' && lowercase_char <= 'z')
        {
            char_count[lowercase_char - 'a']++;
            if (char_count[lowercase_char - 'a'] > 1)
            {
                printf("The key has repeated characters.\n");
                return 0;
            }
        }
    }
    return 1;
}

char cout_letter(char letter, string s)
{
    if (letter >= 'A' && letter <= 'Z')
    {
        int index = letter - 'A';
        return toupper(s[index]);
    }
    else if (letter >= 'a' && letter <= 'z')
    {
        int index = letter - 'a';
        return tolower(s[index]);
    }
    return letter;
}
