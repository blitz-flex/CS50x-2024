#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    int letters = 0, words = 0, sentences = 0;

    float L = 0, S = 0;

    string text = get_string("Text: ");

    letters = count_letters(text);

    words = count_words(text);

    sentences = count_sentences(text);

    // L is the average number of letters per 100 words in the text.
    L = (float) letters / (float) words * 100;

    // S is the average number of sentences per 100 words in the text.
    S = (float) sentences / (float) words * 100;

    float index = 0;
    index = 0.0588 * L - 0.296 * S - 15.8;

    if (index < 1)
        printf("Before Grade 1\n");
    else if (index >= 16)
        printf("Grade 16+\n");
    else
    {
        printf("Grade %d\n", (int) round(index));
    }
}

int count_letters(string text)
{
    int length = 0;

    int i = 0;

    char s = '\0';

    while (text[i])
    {
        s = text[i];

        // check letters to be uppercase or lowercase alphabetical character
        if (islower(s) || isupper(s))
            length++;
        i++;
    }
    return length;
}

int count_words(string text)
{
    int words = 1;

    int i = 0;

    char s = '\0';

    while (text[i])
    {
        s = text[i];

        if (s == 32)
        {
            // handle multiple spaces between words
            while (text[i] == 32)

                i++;

            words++;
        }
        i++;
    }
    return words;
}

int count_sentences(string text)
{
    int sentences = 0;

    int i = 0;

    char s = '\0';

    while (text[i])
    {
        s = text[i];

        if (s == '.' || s == '!' || s == '?')

            sentences++;

        i++;
    }
    return sentences;
}
