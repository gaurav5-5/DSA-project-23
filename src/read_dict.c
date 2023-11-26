#include "read_dict.h"
#include "trie.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

tnode *DICTIONARY;

void load_tree() {

    DICTIONARY = trie_init();
    FILE *dfile = fopen("res/words.txt", "r");
    system("cd");
    // assert(dfile);

    char ch;
    int ind = 0;
    char *word = (char*)malloc(100*sizeof(char));
    while(true) {
        
        f_chin:
            ch = getc(dfile);
        
        if(ch == '\r') goto f_chin;
        if(ch == '\n' || ch == EOF) {
            
            word[ind] = '\0';
            str_to_tree(word);
            ind = -1;
            
            if(ch == EOF) break;

        } else 
            word[ind] = ch;    

        ind++;
    }
    fclose(dfile);
}