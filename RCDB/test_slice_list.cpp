#include "slicelist.h"

void main()
{
	SliceList* list = new SliceList;
	unsigned char* key = new unsigned char[2];
	unsigned char* value = new unsigned char[2];
	key[0] = value[0] = 'a';
	key[1] = value[1] = '\0';
	list->add(Slice(key, 2, value, 2));
	list->add(Slice(key, 2, value, 2));

	SliceList::iterator ita;
	ita = list->Begin();
	while (!ita.isEmpty())
	{ 

		Slice slice = ita.next();
	}
	delete list;
	//Slice a = Slice(key, 2, value, 2);
	//if (true)
	//{
	//	Slice b;
	//	b = a;
	//}
	//Slice c = a;

}