#include "sstable_block.h"
#include "sstable.h"

void main()
{
	SSTable *table = new SSTable();
	table->readIdx();

	unsigned char* file = new unsigned char[2];
	file[0] = 0;
	file[1] = '\0';
	std::string filename = table->getFilename(file, 2);
	SSTableBlock *block = new SSTableBlock(filename);
	block->readBlock();

	
	return;
}
