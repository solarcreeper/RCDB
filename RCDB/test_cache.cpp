#include "cache.h"

void main()
{
	Cache* cache = new Cache();
	unsigned char*  key = new unsigned char[5];
	key[0] = 'A';
	key[1] = 'A';
	key[2] = 'K';
	key[3] = 'M';
	key[4] = '\0';
	Slice result = cache->get(key, 5);
	
}