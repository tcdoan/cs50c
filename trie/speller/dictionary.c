// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27
int dict_size = 0;

// Represents a node in a trie
typedef struct node 
{
    bool is_word;
    struct node *children[N];
} node;

node* root;

bool insert(char* word)
{
    node *x = root;
    for (int i = 0; i < strlen(word); i++)
    {
        int idx = tolower(word[i]) - 'a';
        if (x->children[idx] == NULL) 
        {
            x->children[idx] = malloc(sizeof(node));
            if (x->children[idx] == NULL)
            {
                return false;
            }

            x->is_word = false;
            for (int k = 0; k < N; k++) 
            {
                x->children[idx]->children[k] = NULL;
            }
        }
        x = x->children[idx];
    }
    x->is_word = true;
    dict_size++;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    root = malloc(sizeof(node));
    // Initialize trie
    if (root == NULL)
    {
        return false;
    }

    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        if (!insert(word))
        {
            fclose(file);
            return false;
        }
    }
    
    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *x = root;
    for (int i = 0; i < strlen(word); i++) 
    {
        int idx = tolower(word[i])-'a';
        if (x->children[idx] == NULL) 
        {
            return false;
        }
        x = x->children[idx];
    }
    return x->is_word;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO free memory
    return true;
}
