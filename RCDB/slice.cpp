#include "slice.h"

Slice::Slice()
{
	this->is_deleted = false;
	this->key = NULL;
	this->value = NULL;
	this->key_size = 0;
	this->value_size = 0;
}

Slice::Slice(unsigned char* key, int key_size, unsigned char* value, int value_size)
{
	this->is_deleted = false;
	this->key_size = key_size;
	this->value_size = value_size;

	
	

	if (key_size > 0)
	{
		this->key = new unsigned char[key_size];
		memcpy(this->key, key, key_size);

		/*this->key = new unsigned char[key_size];
		strcpy_s((char*)this->key, key_size, (char*)key);*/
	}
	if (value_size > 0)
	{
		this->value = new unsigned char[value_size];
		memcpy(this->value, value, value_size);

		/*this->value = new unsigned char[value_size];
		strcpy_s((char*)this->value, value_size, (char*)value);*/
	}
}

Slice::~Slice() 
{
	if (this->key_size >0)
	{
		delete[] key;
		this->key = NULL;
	}
	if (this->value_size != NULL)
	{
 		delete[] value;
		this->value = NULL;
	}
}

Slice& Slice::operator =(const Slice& slice)
{
	this->is_deleted = slice.is_deleted;
	if (slice.key == NULL || slice.value == NULL) {
		if (this->key != NULL)
		{
			delete[] this->key;
		}
		this->key = NULL;
		if (this->value != NULL)
		{
			delete[] this->value;
		}
		this->value = NULL;
		this->key_size = 0;
		this->value_size = 0;
		return *this;
	}
	if (this->key != NULL)
	{
		delete[] key;
		key = NULL;
	}
	if (this->value != NULL)
	{
		delete[] value;
		value = NULL;
	}
	if (slice.key_size > 0)
	{
		this->key = new unsigned char[slice.key_size];
		memcpy(this->key, slice.key, slice.key_size);

		//strcpy_s((char*)this->key, slice.key_size, (char*)slice.key);

	}
	if (slice.value_size > 0)
	{
		this->value = new unsigned char[slice.key_size];
		memcpy(this->value, slice.value, slice.key_size);

		//strcpy_s((char*)this->value, slice.value_size, (char*)slice.value);

	}
 	this->key_size = slice.key_size;
	this->value_size = slice.value_size;
	return *this;
}

void Slice::setValue(unsigned char* value, int size)
{
	memcpy(this->value, value, value_size);
	this->value_size = size;
}

void Slice::delValue()
{
	this->is_deleted = true;
}

bool Slice::isDeleted()
{
	return this->is_deleted;
}

void Slice::cancelDelValue()
{
	this->is_deleted = false;
}

unsigned char* Slice::getKey()
{
	return this->key;
}

unsigned char* Slice::getValue()
{
	return this->value;
}

int Slice::getKeySize()
{
	return this->key_size;
}

int Slice::getValueSize()
{
	return this->value_size;
}