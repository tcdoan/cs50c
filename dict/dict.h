#include <stdbool.h>

#define WORD_LEN 50
#define DEF_LEN 500
#define N 27

typedef struct node {
    char def[DEF_LEN];
    struct node * children[N];
} node;

node* ROOT;

bool load(char *data_file);
bool unload();
unsigned int size();
bool lookup(char *word, char* definition);
