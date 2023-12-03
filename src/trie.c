#include "trie.h"

#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include <stdlib.h>
#include <stdio.h>


int tn_index(char letter) {
        
        switch (letter)
        {
        // if case range labels are OK:
        // case 'A' ... 'Z':
        //     letter += 32;
        // case 'a' ... 'z':
        //     index = letter - 97;
        //     break;

        // default:
        //     index = 26;
        //     break;
            
        case '\'':
            return 26;

        default:
            if(letter <= 'Z') letter += 32;
            return (letter - 97);

        }

        return -1;
}

/**
 * Node Creation Function for trie
 * @retval tnode*
 */
tnode *tn_new()
{
    tnode *new = (tnode *)calloc(1, sizeof(tnode));
    assert(new != NULL);

    // Set struct Values
    new->end = false;
    new->letters = (tnode **)malloc(27 * sizeof(tnode *));

    // initialize garbage values to NULL
    for(int i = 0; i < 27; i++) new->letters[i] = NULL;

    return new;
}

/**
 * insert a word inside the dictionary
 * @param *Word pointer to Word to be added
 * @param *Dictionary Pointer to dictionary to add to
 */
void tn_insert(char *Word, tnode *Dictionary)
{

    tnode *current = Dictionary;
    int index = 26;
    int len = strlen(Word);

    char letter;
    for (int i = 0; i < len && ((letter = Word[i]) != '\0'); i++)
    {
        if(letter == ' ' || letter == '.' || letter == ',') break;

        index = tn_index(letter);

        if (current->letters[index] == NULL)
        {
            current->letters[index] = tn_new();
        }
        current = current->letters[index];
    }
    current->end = true;
}

/** Delete word from dicitionary
 * @param *Word word to remove
 * @param *Dictionary trie to delete from
 */
bool tn_delete(char *Word, tnode *Dictionary) 
{
    tnode *current = Dictionary;
    int index = 26;
    int len = strlen(Word);

    char letter;
    for(int i = 0; i < len && ((letter = Word[i]) != '\0'); i++) 
    {
        if(letter == ' ' || letter == '.' || letter == ',') break;

        index = tn_index(letter);

        // word does not exist
        if(current->letters[index] == NULL) return false;
        current = current->letters[index];
    }
    current->end = false;

    // successful deletion
    return true;
}

/** check spelling using trie
 * @param *Word pointer to Word to be checked
 * @param *Dictionary pointer to dictionary to check with
 */
bool check_word(char *Word, tnode *Dictionary)
{

    tnode *current;
    current = Dictionary;
    int index = 26;
    int len = strlen(Word);

    // for (char *letter = Word; *letter != '\0' && *letter != ' ' && *letter != '\n'; letter++)
    for(int i = 0; i < len; i++)
    {

        char letter = Word[i];
        if(letter == '\0' || letter == ' ' || letter == '\n') break;

        index = tn_index(letter);
        current = current->letters[index];
        if (current == NULL)
            return false;
    }
    return current->end;
}

/**
 * @brief  Check an english sentence against a dictionary
 * @note Uses check_word() which ends words at [',' '.' ' '] and so, only requires pointer to first character of word
 * @param  *Sentence: Sentence to be checked
 * @param  *Dictionary: Trie to check against
 * @retval  *true* if no wrongly spelled words, *false* otherwise
 */
bool check_sentence(char *Sentence, tnode *Dictionary)
{

    bool res = true;
    for (char *lptr = Sentence; res && *lptr != '\0'; lptr++)
    {
        if (lptr == Sentence)
            res = check_word(lptr, Dictionary);
        else if (*lptr == ' ')
            res = check_word(++lptr, Dictionary);
    }

    return res;
}

/**
 * @brief  Free up memory used by trie
 * @note   Similar to postorder traversal of BST
 * @param  **head: Pointer to a Pointer Variable containing address of root of tree
 * @retval None
 */
void tn_free(tnode **head)
{
    if (*head == NULL)
        return;
    for (int i = 0; i < 27; i++)
        tn_free(&((*head)->letters[i]));

    if((*head) != NULL) free((*head));
}


/**
 * Dictionary to be preloaded is stored
 * in Plaintext[.txt] format.
 *
 * Each word is on a new line
 *
 * FILE STRUCTURE
 * +-------------------+
 * | word1(\n)         |
 * | word2(\n)         |
 * | ...               |
 * | lastWord(EOF)     |
 * +-------------------+
 */

/**
 * @brief  preload words into trie from res/words.txt
 * @retval Address of head node of created trie
 */
tnode *file_to_trie()
{

    tnode *new = tn_new(), *current;
    current = new;
    FILE *dfile = fopen("./res/words.txt", "r");
    // assert(dfile != NULL);

    char letter;
    int index;

    while ((letter = fgetc(dfile)) != EOF)
    {

        switch (letter)
        {
        // '\r' -> Carriage Return
        // This case is to fix any issues due to presence of \r
        case '\r':
            break;

        case '\n':
            current->end = true;
            current = new;
            break;
        
        default:
            index = tn_index(letter);
            if(current->letters[index] == NULL)
            {
                current->letters[index] = tn_new();
                current->letters[index]->end = false;
            }
            current = current->letters[index];
            break;
        }
    }
    current->end = true;
    fclose(dfile);
    current = NULL;

    return new;
}
