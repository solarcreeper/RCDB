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
	int getKeySize();
	int getValueSize();
	Slice& operator =(const Slice& slice);
private:
	unsigned char* key;
	int key_size;
	unsigned char* value;
	int value_size;
};
#endif // ! SLICE_H
