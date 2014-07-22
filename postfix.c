#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define sizeN sizeof(stackNode2)

/**
 * NOTE: this program can only handle input with numbers less than 10
 * only. This is because the input cannot contain spaces. This was done
 * so that this program can match the input/output as given by the
 * assignment handout.
 */

/** Node structures and types for use with the stack */
struct stackNode2 { 
int data; 
struct stackNode2 *nextPtr; 
}; 
typedef struct stackNode2 stackNode2; 
typedef stackNode2 *stackNode2Ptr; 

/** Evaluate the postfix expression. */
int evaluatePostfixExpression( char *expr ); 
 
/** Evaluate the expression op1 operator op2. */
int calculate2( int op1, int op2, char operator );
 
/** push2 a value on the stack.  */
void push2( stackNode2Ptr *topPtr, int value );
 
/** pop2 a value off the stack.  */
int pop2( stackNode2Ptr *topPtr );
 
/** Determine if the stack is empty.  */
int isEmpty2( stackNode2Ptr topPtr );

/** external funtion in clab_p2 */
int computePostfix(char* postfix);

void push2( stackNode2Ptr *topPtr, int value ){
	stackNode2Ptr stack = *topPtr;
	//get pointer to the first node (which will soon be the second)
	stackNode2Ptr temp = stack->nextPtr;
	//create new node
	stack->nextPtr = malloc(sizeN);
	stack->nextPtr->data = value;
	//add the rest of the stack to the end of the new node
	stack->nextPtr->nextPtr = temp;
}
 
int pop2( stackNode2Ptr *topPtr ){
	stackNode2Ptr stack = *topPtr;
	if (isEmpty2(stack)){
		return 0;
	}
	//get the node to be deleted
	stackNode2Ptr temp = stack->nextPtr;
	//set the new top of the stack
	stack->nextPtr = temp->nextPtr;
	//get the data to return
	int pop2 = temp->data;
	//free the memory
	free(temp);
	return pop2;
}
 
int isEmpty2( stackNode2Ptr topPtr ){
	if (topPtr->nextPtr == NULL){
		return 1;
	}
	return 0;
}

/** assumes given postfix expression is valid */
int evaluatePostfixExpression( char *expr ){
	//create the stack
	stackNode2Ptr stack = malloc(sizeN);
	
	int x, y;
	int i = 0;
	char c = expr[i];
	//read entire expression
	while (c != '\0' && i < 80){
		
		//check what if c is digit or operator
		if (isdigit(c)){
			// c is a number, so push2 it onto stack
			x = c - '0';
			push2(&stack, x);
		} else {
			/* c must be an operator,
			 * so have to pop2 two elements from the stack and 
			 * apply the operation */
			 x = pop2(&stack);
			 y = pop2(&stack);
			 push2(&stack, calculate2(x, y, c));
		}
		c = expr[++i];
	}
	return pop2(&stack);
} 
 
int calculate2( int op1, int op2, char operator ){
	int ans = 0;
	/* check operator and apply appropriate operation
	 * NOTE: i decided to use a loop to apply the exponent
	 * function as opposed to using pow() in the c math 
	 * library which would require additional compile flags */
	switch (operator){
		case ('+'):	{
			ans = (op2 + op1);
			break;
		}
		
		case ('-'): {
			ans = (op2 - op1);
			break;
		}
		
		case ('*'): {
			ans = (op2 * op1);
			break;
		}
		
		case ('/'): {
			ans = (op2 / op1);
			break;
		}
		
		case ('^'): {
			int i = 0;
			ans = 1;
			//loop to apply exponent operation
			for (i = 0; i < op1; i++){
				ans = ans * op2;
			}
			break;
		}
		
		case ('%'): {
			ans = (op2 % op1);
			break;
		}
	}
	return ans;
}

int computePostfix(char* postfix){
	return evaluatePostfixExpression(postfix);;
}
