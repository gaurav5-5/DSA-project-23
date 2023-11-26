#ifndef SPL_TRIE_H
#define SPL_TRIE_H

#include <stdbool.h>

typedef
struct trie_node {
    bool end;
    struct trie_node **ch;
}
tnode;

tnode * trie_init();

void str_to_tree(char *str);
bool checkspell(char *str);

#endif // !SPL_TRIE_H