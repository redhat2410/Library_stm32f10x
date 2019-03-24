#define __STACK_H


struct Node_Stack{
	unsigned int Data;
	struct Node_Stack* Next;
};

struct Stack{
	struct Node_Stack* Top;
};

void Init_Stack(struct Stack* stack);
void Push(struct Stack* stack, unsigned int x);
unsigned int Pop(struct Stack* stack);
