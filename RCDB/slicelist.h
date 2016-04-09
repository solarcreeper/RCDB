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
	void add(Slice& slice);

public:
	SliceListNode* Begin();

private:
	SliceListNode* slice_list;

	class List_Iterator
	{
		SliceListNode* curr;

	public:
		void operator =(SliceListNode* ptr)
		{
			curr = ptr;
		}

		Slice next()
		{
			Slice p;
			if (curr->next)
			{
				p = curr->next->slice;
				curr = curr->next;
				return Slice(p.getKey(), p.getKeySize(), p.getValue(), p.getValueSize());
			}
			return Slice();
		}

		bool isEmpty()
		{
			if (curr == NULL)
			{
				return true;
			}

			if (curr->next)
			{
				return false;
			}
			return true;
		}
	};

public:
	typedef List_Iterator iterator;
};
#endif // ! SLICELIST_H
