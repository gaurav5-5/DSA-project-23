#include "trie.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


extern tnode *DICTIONARY;

tnode * trie_init() {
    tnode * new = (tnode*)calloc(1, sizeof(tnode));
    new->end = false;
    new->ch = (tnode**)calloc(27, sizeof(tnode*)); // calloc to prevent garbage value-
    
    return new;
}

void str_to_tree(char *str) {

    tnode *cur, *prev;
    cur = prev = DICTIONARY;
    int ind = 26;

    for(char *ch = str; *ch != '\0'; ch++) {

        switch (*ch)
        {
        case '\'':
            ind = 26;
            break;
            
        default:
            if(*ch <= 'Z') *ch = (char)((int)(*ch) + 32);
            ind = *ch-97;
            break;
        }
        // printf("%c", (char)(ind+65));
        if(cur->ch[ind] == NULL) {
            cur->ch[ind] = trie_init();
        }
        prev = cur;
        cur = cur->ch[ind];
    }
    if(!prev->end) prev->end = true;
    // printf("\n");
}

bool checkspell(char *str) {
    tnode *prev, *cur;
    prev = cur = DICTIONARY;
    int ind = 26;

    for(char *ch = str; *ch != '\0'; ch++) {
        
        prev = DICTIONARY;
        switch(*ch)
        {
            case '\'':
            ind = 26;
            break;

            default:
            if(*ch <= 'Z') *ch = (char)((int)(*ch) + 32);
            ind = *ch-97;
            break;
        }
        cur = cur->ch[ind];
        if(cur == NULL) return false;
    }
    if(!(prev->end)) return false;
    return true;
}
