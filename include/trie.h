#ifndef SPL_TRIE_H
#define SPL_TRIE_H

#include <stdbool.h>

// structure definition for trie
typedef
struct trie_node {
    bool end;
    struct trie_node **letters;
}
tnode;

tnode *tn_new();

void tn_insert(char *Word, tnode *Dictionary);
bool tn_delete(char *Word, tnode *Dictionary);

bool check_word(char *Word, tnode *Dictionary);
bool check_sentence(char *Word, tnode *Dictionary);

void tn_free(tnode **head);

tnode *file_to_trie();

int tn_index(char letter);

#endif // !SPL_TRIE_H