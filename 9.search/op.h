#include "ST.h"

#ifndef TNODETYPE
#define TNODETYPE
typedef bstnode tnode;
#endif

Status Lrotate(tnode **root);
Status Rrotate(tnode **root);
Status LRrotate(tnode **root);
Status RLrotate(tnode **root);