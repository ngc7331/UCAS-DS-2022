#include <../ds.h>

// NOT FINISHED
typedef int AtomType;
typedef enum {ATOM, LIST} ELemTag;
typedef struct __GLNode {
    ELemTag tag;
    union {
        AtomType atom;
        struct {
            struct __GLNode *hp, *tp;
        } ptr;
    };
} GLNode, *Glist;