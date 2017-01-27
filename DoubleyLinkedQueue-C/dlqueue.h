

typedef struct dnode* Dnode;
struct dnode{
	int val;
	Dnode next;
	Dnode prev;
};

typedef struct queue* Queue;
struct queue{
	Dnode front;
	Dnode back;
};

Queue makeQueue();

void enqueue(Queue qp, int val);

int nonempty(Queue qp);

int dequeue(Queue qp);


