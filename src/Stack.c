#include "stdlib.h"
#include "Stack.h"


void Init_Stack(struct Stack* stack){
	stack->Top = NULL;
}

int IsEmpty_Stack(struct Stack stack){
	return (stack.Top == NULL);
}

struct Node_Stack* addNode_Stack(unsigned int x){
	struct Node_Stack* tmp = (struct Node_Stack*)malloc(sizeof(struct Node_Stack));
	tmp->Next = NULL;
	tmp->Data = x;
	return tmp;
}

void Push(struct Stack* stack, unsigned int x){
	struct Node_Stack* tmp = addNode_Stack(x);
	tmp->Next = stack->Top;
	stack->Top = tmp;
}

unsigned int Pop(struct Stack* stack){
	if(!IsEmpty_Stack(*stack)){
		unsigned int x = stack->Top->Data;
		stack->Top = stack->Top->Next;
		return x;
	}
	return NULL;
}

