#ifndef HASH_TABLE
#define HASH_TABLE

class hashtable
{
public:
	hashtable();
	~hashtable();
	int getCapacity();
	int getSize();
	void insert(int elem);
	int hash(int elem);
private:
	LinkedList list;
	int* buckets;
	int size;
	int cap;
	double load;
};








#endif

