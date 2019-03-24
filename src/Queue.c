#include "stdlib.h"
#include "Queue.h"

//Initilization Queue
void Init(struct Queue *queue){
	queue->Front = NULL;
	queue->Rear = NULL;
	queue->count = 0;
}

//function check queue is empty
int IsEmpty_Queue(struct Queue queue){
	if(queue.count == 0) return 1;
	return 0;
}
//Create new Node_Queue in queue
struct Node_Queue* addNode_Queue(unsigned int x){
	struct Node_Queue *tmp = (struct Node_Queue*)malloc(sizeof(struct Node_Queue));
	tmp->Next = NULL;
	tmp->Data = x;
	return tmp;
}

//Add Node_Queue in tail of Queue
void Enqueue(struct Queue *queue, unsigned int x){
	struct Node_Queue *tmp = addNode_Queue(x);
	//Kiem tra hang doi da co Object nao chua
	if(IsEmpty_Queue(*queue)){
		//neu chua co thi con tro Front va con tro Rear deu tro toi Node_Queue Tmp
		queue->Front = tmp;
		queue->Rear = tmp;
	}
	else{
		//nguoc lai thi con tro Rear se tro toi con tro Next la tmp
		queue->Rear->Next = tmp;
		queue->Rear = tmp;
	}
	queue->count++;
}
//Get Item and remove frist Node_Queue in Queue
unsigned int Dequeue(struct Queue *queue){
	//Kiem tra hang doi neu rong thi tra ve NULL
	if(IsEmpty_Queue(*queue)) return NULL;
	//nguoc lai thi return ve gia tri dau tien vao hang doi
	else{
		unsigned int x = queue->Front->Data;
		if(queue->count == 1) Init(queue);
		else queue->Front = queue->Front->Next;
		queue->count--;
		return x;
	}
}
