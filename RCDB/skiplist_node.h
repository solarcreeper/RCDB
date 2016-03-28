#ifndef SKIPLIST_NODE_H
#define SKIPLIST_NODE_H
#define MAX_LEVEL 4
#include "slice.h"

class SkiplistNode 
{
public:
	Slice slice;
	SkiplistNode* forward;

	SkiplistNode();
	~SkiplistNode();
	SkiplistNode& operator=(const SkiplistNode* &node);
private:

};

#endif // !SKIPLIST_NODE_H


