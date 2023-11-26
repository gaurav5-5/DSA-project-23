#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "read_dict.h"
#include "admin.h"
#include "trie.h"

extern tnode *DICTIONARY;

int main() {

    int ex = 0;
    char word[50];

    printf("Loading tree...\n");
    load_tree();
    printf("Tree loaded successfully\n");


    do {
        if(!login_status())
            printf("MENU\n  0. EXIT\n  1. ADD WORD\n  2. CHECK WORD\n  3. LOGIN\n>>> ");
        else
            printf("MENU\n  0. EXIT\n  1. ADD WORD\n  2. CHECK WORD\n  3. LOGOUT\n>>> ");

        scanf("%d", &ex);

        switch (ex)
        {
        case 0:
            printf("Exiting...\n");
            break;
        
        case 1:
            if(login_status()) {
                printf("Enter Word to add: ");
                scanf("%s", word);

                str_to_tree(word);
            } else {
                printf("Error 403: FORBIDDEN\n");
            }
            break;

        case 2:
            printf("Enter Word to Check: ");
            scanf("%s", word);

            if(checkspell(word)) {
                printf("%s is spelled correct\n", word);
            } else {
                printf("%s is spelled wrogn\n", word);
            }
            break;

        case 3:
            if(login_status()) logout();
            else login();
            break;
        
        default:
            printf("Invalid\n");
            break;
        }
    }
    while(ex);

    return EXIT_SUCCESS;
}