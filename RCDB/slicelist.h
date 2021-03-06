#ifndef  SLICELIST_H
#define SLICELIST_H
#include "slice.h"
#include "iterator.h"

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

	class List_Iterator : public Iterator
	{
		SliceListNode* curr;
		SliceListNode* head;
	public:
		void init(void* ptr)
		{
			curr = (SliceListNode*)ptr;
			head = (SliceListNode*)ptr;
		}

		void init(void* ptr, int(*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size), unsigned char* key, int key_size, std::string data_path)
		{
			return;
		}

		Slice pre()
		{
			if (curr == head || head->next == curr)
			{
				curr = head;
				return Slice();
			}

			Slice p;
			SliceListNode* it = head->next;
			while (it->next != curr)
			{
				it = it->next;
			}
			p = it->slice;
			curr = it;
			return Slice(p.getKey(), p.getKeySize(), p.getValue(), p.getValueSize());
		}

		Slice next()
		{
			Slice p;
			if (curr == NULL)
			{
				return Slice();
			}

			if (curr->next)
			{
				p = curr->next->slice;
				curr = curr->next;
				return Slice(p.getKey(), p.getKeySize(), p.getValue(), p.getValueSize());
			}
			return Slice();
		}

		Slice current()
		{
			Slice p;
			if (curr == NULL)
			{
				return Slice();
			}

			if (curr->slice.getKey() > 0)
			{
				p = curr->slice;
			}
			return Slice(p.getKey(), p.getKeySize(), p.getValue(), p.getValueSize());
		}

		bool isTail()
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
		
		bool isHead()
		{
			if (curr == head || head->next == curr)
			{
				return true;
			}
			return false;
		}
	};

public:
	typedef List_Iterator iterator;
};
#endif // ! SLICELIST_H
