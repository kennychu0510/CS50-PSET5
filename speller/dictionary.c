// Implements a dictionary's functionality
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <cs50.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 475255;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    char *checkWord = malloc(strlen(word) + 1);

    strcpy(checkWord, word);

    int i = hash(word);

    //convert word to lowercase
    for (int j = 0; j < strlen(checkWord); j++){
        checkWord[j] = tolower(checkWord[j]);
    }

    for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next){
        if (strcmp(tmp->word, checkWord) == 0){
            free(checkWord);
            return true;
        }
    }
    free(checkWord);
    return false;

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    int hashNumber = 0;

    //if word contains one letter only
    if (word[1] == '\0')
    {
        hashNumber = toupper(word[0]) - 'A';
    }

    else if (word[2] == '\0')
    {
        hashNumber = 26 * (toupper(word[0]) - 'A' + 1) + toupper(word[1]) - 'A';
    }
    else if (word[3] == '\0')
    {
        hashNumber = 26 + 676 * (toupper(word[0]) - 'A' + 1) + 26 * (toupper(word[1]) - 'A') + toupper(word[2]) - 'A';
    }
    else
    {
        hashNumber = 26 + 676 + 17576 * (toupper(word[0]) - 'A' + 1) + 676 * (toupper(word[1]) - 'A') + 26 * (toupper(word[2]) - 'A') + toupper(word[3]) - 'A';
    }

    return hashNumber;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dic = fopen (dictionary, "r");
    if (dic == NULL){
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(dic, "%s", word) != EOF){
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(dic);
            return false;
        }

        int index = hash(word);
        strcpy(n->word, word);
        n->next = NULL;

        if (table[index] == NULL)
        {
            table[index] = n;
        }

        else
        {
            node *p = table[index];
            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = n;
        }
    }
    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;
    for (int i = 0; i < N; i++){
        for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next){
            count++;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++){
        while (table[i] != NULL)
            {
                node *tmp = table[i]->next;
                free(table[i]);
                table[i] = tmp;
            }
    }
    return true;
}
