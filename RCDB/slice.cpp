#include "slice.h"

Slice::Slice()
{
	this->key = NULL;
	this->value = NULL;
	this->key_size = 0;
	this->value_size = 0;
}

Slice::Slice(unsigned char* key, int key_size, unsigned char* value, int value_size)
{
	this->key_size = key_size;
	this->value_size = value_size;
	this->key = new unsigned char[key_size];
	memcpy(this->key, key, key_size);
	//this->key[key_size] = '\0';
	this->value = new unsigned char[value_size];
	memcpy(this->value, value, value_size);
	//this->value[value_size] = '\0';
}

Slice::~Slice() 
{
	delete[] key;
	delete[] value;
	
}

Slice& Slice::operator =(const Slice& slice)
{
	if (slice.key == NULL) {
		this->key = NULL;
		this->value = NULL;
		this->key_size = 0;
		this->value_size = 0;
		return *this;
	}
	if (this->key != NULL)
	{
		delete[] key;
	}
	if (this->value != NULL)
	{
		delete[] value;
	}

 	this->key_size = slice.key_size;
	this->value_size = slice.value_size;
	this->key = new unsigned char[key_size];
	this->value = new unsigned char[value_size];
	memcpy(this->key, slice.key, key_size);
	memcpy(this->value, slice.value, value_size);
	//this->key[key_size] = '\0';
	//this->value[value_size] = '\0';
	return *this;
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