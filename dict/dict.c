#include "dict.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

void removeSpaces(char *str) 
{ 
    int count = 0; 
    for (int i = 0; str[i]; i++) 
    {
        if (str[i] != ' ') 
        {
            str[count++] = str[i];
        }
    }
    str[count] = '\0'; 
} 

bool split_line(char *buf, char *word, char *desc)
{
    char *def = buf;
    char *w = strtok_r(buf, "|", &def);
    strcpy(word, w);
    strcpy(desc, def);
    return true;
}

bool insert(char *word, char *desc) 
{
    removeSpaces(word);    
    node *x = ROOT;
    for (int i=0; i < strlen(word); i++)
    {
        int idx = tolower(word[i]) - 'a';
        if (x->children[idx] == NULL)
        {
            x->children[idx] = malloc(sizeof(node));
            for (int k = 0; k < N; k++)
            {
                x->children[idx]->children[k] = NULL;
            }
        }
        x = x->children[idx];
    }
    strcpy(x->def,desc);
    return true;
}

bool load(char *data_file)
{
    ROOT = malloc(sizeof(node));
    for (int i = 0; i < N; i++)
    {
        ROOT->children[i] = NULL;
    }

    FILE* fd = fopen(data_file, "r");    
    for (;;)    
    {
        char buf[WORD_LEN + DEF_LEN];
        fgets(buf, WORD_LEN + DEF_LEN-1, fd);
        if (buf == NULL || feof(fd))
        {
            break;
        }
        char word[WORD_LEN];
        char definition[DEF_LEN];
        if (!split_line(buf, word, definition))
        {
            return false;
        }        
        if (!insert(word, definition))
        {
            return false;
        }
    }
    return true;
}

bool lookup(char *word, char* desc)
{
    node *x = ROOT;
    for (int i=0; i < strlen(word); i++)
    {
        int idx = tolower(word[i]) - 'a';
        if (x->children[idx] == NULL)
        {
            return false;
        }
        x = x->children[idx];
    }
    if (x->def == NULL)
    {
        return false;
    }

    strcpy(desc, x->def);
    return true;
}

int main(int argc, char** argv)
{
    char *data_file = argv[1];
    if (data_file == NULL || strlen(data_file) < 1)
    {
        printf("Please enter name of data file when you run this program\n");
        return 1;
    }

    if (!load(data_file))
    {
        printf("Error loading data file.");
        return 1;
    }

    char away_desc[DEF_LEN];
    if (!lookup("away", away_desc)) 
    {
        printf("'away' not found");
    } 
    else {
        printf("away_desc = %s ", away_desc);
    }
    
    char blahahahah_desc[DEF_LEN];
    if (!lookup("blahahahah", blahahahah_desc)) 
    {
        printf("'blahahahah' not found");
    }
    else
    {
        printf("blahahahah_desc = %s ", blahahahah_desc);    
    }
}
