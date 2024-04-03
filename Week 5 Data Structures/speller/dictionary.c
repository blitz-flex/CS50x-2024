// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 26;
int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_index = hash(word);

    // create cursor variable

    node *cursor = table[hash_index];

    while (cursor != NULL)
    {
        // check if the words

        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file

    FILE *source = fopen(dictionary, "r");

    if (source == NULL)
    {
        return false;
    }

    // Declare a buffer to read one word at a time

    char str[LENGTH + 1];

    // Scan words until EOF

    while (fscanf(source, "%s", str) != EOF)
    {
        // Create a new node use malloc

        node *tmp = malloc(sizeof(node));

        if (tmp == NULL)
        {
            return false;
        }

        // Copy words from dictionary to new_node

        strcpy(tmp->word, str);

        // use hash function

        int hash_index = hash(str);

        // If hash table is empty, set next pointer to null

        if (table[hash_index] == NULL)
        {
            tmp->next = NULL;
        }
        else
        {
            tmp->next = table[hash_index];
        }

        // point the header to tmp

        table[hash_index] = tmp;

        word_count++;
    }

    // Close the dictionary file

    fclose(source);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    return word_count;
}

void freepon(node *n)
{
    if (n->next != NULL)
    {
        freepon(n->next);
    }
    free(n);
}
// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            freepon(table[i]);
        }
    }
    return true;
}
