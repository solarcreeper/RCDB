#include "skiplist_node.h"

SkiplistNode::SkiplistNode() 
{
	slice = Slice();
	for (int i = 0; i < MAX_LEVEL; i++) 
	{
		forward[i] = NULL;
	}
}

SkiplistNode::~SkiplistNode()
{
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		if (forward[i] != NULL)
		{
			delete forward[i];
		}
	}
}

SkiplistNode& SkiplistNode::operator=(const SkiplistNode* &node)
{
	slice = node->slice;
	for (int i = 0; i < MAX_LEVEL; i++) 
	{
		forward[i] = node->forward[i];
	}
	return *this;
}

