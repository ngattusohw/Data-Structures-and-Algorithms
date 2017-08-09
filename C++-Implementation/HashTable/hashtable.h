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
	void adjust();
	void increment();
	void decrement();
	bool search(int elem);
private:
	LinkedList* buckets;
	int size;
	int cap;
	double load;
	int hash(int elem);
};








#endif

