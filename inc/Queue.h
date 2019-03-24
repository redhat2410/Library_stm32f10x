#define __QUEUE_H

struct Node_Queue{
	unsigned int Data;
	struct Node_Queue* Next;
};

struct Queue{
	struct Node_Queue* Front;
	struct Node_Queue* Rear;
	int count;
};

void Init(struct Queue *queue);
void Enqueue(struct Queue *queue, unsigned int x);
unsigned int Dequeue(struct Queue *queue);
