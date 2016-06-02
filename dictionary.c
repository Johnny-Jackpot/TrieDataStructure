/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

unsigned int word_counter = 0;
NODE* root;
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    NODE* tmp = root;
    int letter;
    for (int i = 0, n = strlen(word); i < n; i++) {
        if (isalpha(word[i])) {
            letter = tolower(word[i]) - 'a';
        } else if (word[i] == '\'') {
            letter = 26;
        }
        
        if (tmp -> next[letter] == NULL) {
            return false;
        } else {
            tmp = tmp -> next[letter];
        }
    }
    
    return tmp -> isword;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */


bool load(const char* dictionary) {
    FILE* dict = fopen(dictionary, "r");
    if (dict == NULL) {
        fclose(dict);
        return false;
    }
        
    root = malloc(sizeof(NODE));
    if (root == NULL) 
        return false;
    root -> isword = false;
    for (int i = 0; i < 27; i++) {
        root -> next[i] = NULL;
    }
    
    int letter;
    NODE* tmp = root;
    for (int c = fgetc(dict); c != EOF; c = fgetc(dict)) {
        if (isalpha(c)) 
            letter = c - 'a';
        else if (c == '\'') 
            letter = 26;
        else if (c == '\n') {
            tmp -> isword = true;
            tmp = root;
            word_counter++;
            continue;
        }
        
        if (tmp -> next[letter] == NULL) {
            tmp -> next[letter] = malloc(sizeof(NODE));
            if (tmp -> next[letter] == NULL) 
                return false;
            tmp = tmp -> next[letter];
            tmp -> isword = false;
            for (int i = 0; i < 27; i++) {
                tmp -> next[i] = NULL;
            }
        } else {
            tmp = tmp -> next[letter];
        }
    }
    
    fclose(dict);    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void) {
    unsigned int* ptr = &word_counter;
    return *ptr;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    delete_node(root);
    return true;
}
void delete_node(NODE* node) {
    NODE* tmp = node;
    for (int i = 0; i < 27; i++) {
        if (tmp -> next[i] != NULL)
            delete_node(tmp -> next[i]);
    }
    free(tmp);
    return;
}
