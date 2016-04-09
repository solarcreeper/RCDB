#include "slicelist.h"

SliceList::SliceList()
{
	this->slice_list = new SliceListNode();
	this->slice_list->slice = Slice();
	this->slice_list->next = NULL;
}

SliceList::~SliceList()
{
	SliceListNode* it = this->slice_list;
	while (it)
	{
		this->slice_list = this->slice_list->next;
		delete it;
		it = this->slice_list;
		it = NULL;
	}
}

void SliceList::add(Slice& slice)
{
	SliceListNode* it = this->slice_list;
	while (it->next)
	{
		it = it->next;
	}
	
	SliceListNode* node = new SliceListNode;
	node->slice = Slice(slice.getKey(), slice.getKeySize(), slice.getValue(), slice.getValueSize());
	node->next = NULL;

	it->next = node;
}

SliceListNode* SliceList::Begin()
{
	if (this->slice_list)
	{
		return this->slice_list;
	}
	return NULL;
}