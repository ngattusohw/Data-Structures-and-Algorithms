#ifndef LINKED_LIST
#define LINKED_LIST

class linkedlist
{
public:
	linkedlist();
	~linkedlist();
	void insertLast(int elem);
	void insertAt(int index, int elem);
	int removeLast();
	int removeAt(int index);
	int getSize();
	bool findElement(int elem);
private:
	int size;
	class Node
	{
	public:
		Node();
		~Node();
	private:
		Node* next;
		int elem;
	};
	Node* head;
	Node* tail;
};








#endif

