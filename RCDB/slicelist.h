#ifndef  SLICELIST_H
#define SLICELIST_H
#include "slice.h"

struct SliceListNode
{
	Slice slice;
	SliceListNode* next;
};

class SliceList
{
public:
	SliceList();
	~SliceList();
	void add(Slice slice);

private:
	SliceListNode* slice_list;

private:
	SliceListNode* slice_list;

	class List_Iterator
	{
		SliceListNode* curr;
		Slice p;

	public:
		void operator =(SliceListNode* ptr)
		{
			curr = ptr;
			p = Slice();
		}

		Slice& next()
		{
			p = Slice();
			if (curr->next)
			{
				p = curr->next->slice;
				curr = curr->next;
			}
			return p;
		}

		bool isEmpty()
		{
			if (curr->next)
			{
				return false;
			}
			return true;
		}
	};
};
#endif // ! SLICELIST_H
