#ifndef DB_H
#define DB_H
#include "cache.h"
#include "mem_table.h"
#include "sstable_filter.h"
#include "options.h"
#include "slicelist.h"

class DB
{
public:
	DB(Options option = Options());
	~DB();

	Slice get(unsigned char* key, int key_size);
	bool put(unsigned char* key, int key_size, unsigned char* value, int value_size);
	
public:
	bool batchPut(unsigned char* key, int key_size, unsigned char* value, int value_size);
	Slice batchGet(unsigned char* key, int key_size);
	bool writeBatch();
	Options getOption();
	
public:
	void printList();
	void printListToFile();

public:
	SkipListNode* memBegin();
	SliceListNode* batchBegin();
	SSTable* dbBegin();

private:
	void saveData();

private:
	Cache* cache;
	MemTable* mem_table;
	MemTable* mem_table_batch;
	SSTableFilter* filter;

private:
	SliceList* batch_result;

private:
	bool write_table_done;
	bool is_batch_success;
	Options option;

private:
	class DB_Iterator
	{
	private:
		SSTableBlock* block;
		SSTable::index_iterator ita;
		SkipList::iterator list_ita;

		unsigned char* key;
		int key_size;
		std::string path;

	public:

		DB_Iterator(unsigned char* key, int key_size, std::string data_path = "./data/")
		{
			this->key = key;
			this->key_size = key_size;
			this->path = data_path;
		}

		~DB_Iterator()
		{
			if (this->block != NULL)
			{
				delete block;
				this->block = NULL;
			}
		}
		/*void setLocation(unsigned char* key, int key_size, SSTable* index)
		{
			std::string file = index->getFilename(this->key, this->key_size);
			this->ita = index->indexBegin();
			while ((!ita.isEmpty()))
			{
				std::string next = ita.next();
				if (next == file)
				{
					break;
				}
			}
			if (this->block != NULL)
			{
				block->saveBlock();
				delete block;
				this->block = NULL;
			}

			this->block = new SSTableBlock(file, this->path);
			this->block->readBlock();
			this->list_ita = this->block->getBlock()->Begin();

			this->toCurrKey();
		}*/

		void operator =(SSTable* index)
		{
			std::string file = index->getFilename(this->key, this->key_size);
			this->ita = index->indexBegin();
			while ((!ita.isEmpty()))
			{
				std::string next = ita.next();
				if (next == file)
				{
					break;
				}
			}
			if (this->block != NULL)
			{
				block->saveBlock();
				delete block;
				this->block = NULL;
			}

			this->block = new SSTableBlock(file, this->path);
			this->block->readBlock();
			this->list_ita = this->block->getBlock()->Begin();

			this->toCurrKey();
		}
		Slice pre()
		{
			if (list_ita.isHead())
			{
				if (ita.isHead())
				{
					return Slice();
				}
				else 
				{
					std::string file = ita.pre();
					this->reloadBlock(file);
					Slice s = toTail();
					while ((s.getKeySize() == 0) && (!ita.isHead()))
					{
						s = pre();
					}
					return Slice(s.getKey(), s.getKeySize(), s.getValue(), s.getValueSize());
				}
			}
			else
			{
				Slice s = list_ita.pre();
				return Slice(s.getKey(), s.getKeySize(), s.getValue(), s.getValueSize());
			}
		}

		Slice next()
		{
			if (list_ita.isEmpty())
			{
				if (ita.isEmpty())
				{
					return Slice();
				}
				else
				{
					std::string file = ita.next();
					this->reloadBlock(file);
					Slice s = list_ita.next();
					while (s.getKeySize() == 0 && (!ita.isEmpty()))
					{
						s = next();
					}
					return Slice(s.getKey(), s.getKeySize(), s.getValue(), s.getValueSize());
				}
			}
			else
			{
				Slice s = list_ita.next();
				return Slice(s.getKey(), s.getKeySize(), s.getValue(), s.getValueSize());
			}
		}

		Slice curr()
		{
			return list_ita.current();
		}

		bool isTail()
		{
			if (list_ita.isEmpty() && ita.isEmpty())
			{
				return true;
			}
			return false;
		}

		bool isHead()
		{
			if (list_ita.isHead() && ita.isHead())
			{
				return true;
			}
			return false;
		}

	private:
		void reloadBlock(std::string file)
		{
			if (this->block != NULL)
			{
				delete this->block;
			}
			this->block = new SSTableBlock(file, this->path);
			this->block->readBlock();
			this->list_ita = this->block->getBlock()->Begin();
		}

		//将迭代器迭代到当前的key
		void toCurrKey()
		{
			while (!list_ita.isEmpty())
			{
				Slice s = list_ita.next();
				if (compare(s.getKey(), s.getKeySize(), this->key, this->key_size) == 0)
				{
					break;
				}
			}
		}

		Slice toTail()
		{
			Slice s;
			while (!list_ita.isEmpty())
			{
				s = list_ita.next();
			}
			return Slice(s.getKey(), s.getKeySize(), s.getValue(), s.getValueSize());
		}

		int compare(unsigned char* a, int lenth_a, unsigned char* b, int lenth_b)
		{

			int size = lenth_a;
			if (size > lenth_b)
			{
				size = lenth_b;
			}
			for (int i = 0; i < size; i++)
			{
				if (a[i] < b[i])
				{
					return -1;
				}
				if (a[i] > b[i])
				{
					return 1;
				}
			}
			if (lenth_a == lenth_b)
			{
				return 0;
			}
			if (lenth_a > lenth_b)
			{
				return 1;
			}
			else
			{
				return -1;
			}
		}

	};

public:
	typedef SkipList::iterator mem_iterator;
	typedef SliceList::iterator batch_iterator;
	typedef DB::DB_Iterator db_iterator;
};

#endif // !DB_H

