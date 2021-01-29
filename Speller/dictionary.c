// Implements a dictionary's functionality

#include <stdbool.h>

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

unsigned int wordCount;


// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{

   // transform the word given to lower case.
   char lowerWord[LENGTH + 1];
   for (int i = 0; i < strlen(word); i++)
   {
       lowerWord[i] = tolower(word[i]);
   }

    lowerWord[strlen(word)] = '\0'; // adding \0 to show the end of the string
    
    int head = hash(lowerWord);

    // set a cursor to follow each word
    node *cursor = table[head];

    // go through each word if the list is not NULL to check if it muches
    while (cursor != NULL)
    {
        if (strcasecmp(lowerWord, cursor->word) == 0)
        {
            return true;
        }

        cursor = cursor->next; // go to next word
    }

    return false;
}

// Hashes word to a number
// hash find here and modified : https://codereview.stackexchange.com/questions/194807/hashtable-implementation-c
unsigned int hash(const char *word)
{
    unsigned int hashVal = 0;
    for( int i = 0; i < strlen(word);i++)
    {
        hashVal += (hashVal << 2) ^ word[i];
    }

    return hashVal % N; // if hashVal is sup to N using % N to have
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];

    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;
    }

    //scan the file word by word
    while (fscanf(file, "%s/n", word) != EOF)
    {
        // Give memory the new words
        node *newWord = malloc(sizeof(node));

        //return false if there is no memory
        if (newWord == NULL)
        {
            return false;
        }

        strcpy(newWord->word, word); // copy word to newWord

        unsigned int head = hash(word); // hash the word to get the number

        newWord->next = table[head]; // join the next pointer
        table[head] = newWord; // insert the new word to the list
        wordCount++; // count number of words

    }

    fclose(file); // close the file open

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // condition fi there are words found on file return there numbers
    if (wordCount != 0)
    {
        return wordCount;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *head = NULL;
    node *cursor = head;

    // to free memory helpin with temp to not loose cursor
    while (cursor != NULL)
    {
        node *temp = cursor;
        cursor = cursor->next;
        free(temp);
    }

    return true;
}
