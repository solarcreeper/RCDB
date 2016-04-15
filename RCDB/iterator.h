#ifndef ITERATOR_H
#define ITERATOR_H
#include "slice.h"

class Iterator
{
public:
	virtual Slice pre() = 0;
	virtual Slice next() = 0;
	virtual Slice current() = 0;
	virtual bool isHead() = 0;
	virtual bool isTail() = 0;
	virtual void init(void* ptr);
	virtual void init(void* ptr, int(*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size), unsigned char* key, int key_size, std::string data_path);
};
#endif // !ITERATOR_H

