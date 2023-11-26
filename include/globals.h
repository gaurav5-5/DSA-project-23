#ifndef SPL_MAIN
# define EXTERN
# define INIT(...) = __VA_ARGS__
#else
# define EXTERN extern
# define INIT(...)
#endif

#include "trie.h"

// Global Dictionary holder
EXTERN tnode *DICTIONARY INIT(trie_init());

