#ifndef SLICE_H
#define SLICE_H
#include <string>

class Slice {
public:
	explicit Slice();
	explicit Slice(unsigned char* key, int key_size, unsigned char* value, int value_size);
	~Slice();
	unsigned char* getKey();
	unsigned char* getValue();
	void setValue(unsigned char* value, int size);
	void delValue();
	bool isDeleted();
	void cancelDelValue();
	int getKeySize();
	int getValueSize();

public:
	Slice& operator =(const Slice& slice);

private:
	unsigned char* key;
	int key_size;
	unsigned char* value;
	int value_size;
	bool is_deleted;
};
#endif // ! SLICE_H
