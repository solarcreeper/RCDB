#ifndef ITERATOR_H
#define ITERATOR_H
#include "slice.h"

class Iterator
{
public:
	virtual ~Iterator() = 0;

	virtual Slice pre() = 0;
	virtual Slice next() = 0;
	virtual Slice current() = 0;
	virtual bool isHead() = 0;
	virtual bool isTail() = 0;
};
#endif // !ITERATOR_H

