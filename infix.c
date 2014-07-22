#include <stdio.h>
#include <stdlib.h>
#include "postfix.h"
#define sizeN sizeof(StackNode)

/**
 * NOTE: this program can only handle input with numbers less than 10
 * only. This is because the output contains no spaces. This was done
 * so that this program can match the input/output as given by the
 * assignment handout.
 */

/** Node structures and types for use with the stack */
struct stackNode { 
char data; 
struct stackNode *nextPtr; 
}; 
typedef struct stackNode StackNode; 
typedef StackNode *StackNodePtr; 

/** enumerates the operators according to their precidence */
enum Operator {Add = 1, Subtract = 1, Multiply = 2, Divide = 2, Modulus = 2, Exponent = 3, LeftBracket = 4, RightBracket = 5};

/** Convert the infix expression to postfix notation. */
void convertToPostfix( char infix[], char postfix[] );
 
/** Determine if c is an operator.  */
int isOperator( char c );
 
/** Determine if the precedence of operator1 is less than, equal to, or greater than 
 * the precedence of operator2. The function returns -1, 0 and 1, respectively.  */
int precedence( char operator1, char operator2 );
 
/** Push a value on the stack.  */
void push( StackNodePtr *topPtr, char value );
 
/** Pop a value off the stack.  */
char pop( StackNodePtr *topPtr );
 
/** Return the top value of the stack without popping the stack. */
char stackTop( StackNodePtr topPtr ); 
 
/** Determine if the stack is empty.  */
int isEmpty( StackNodePtr topPtr );

/** function to get postfix expression from external program */
int compute(char* infix);

void convertToPostfix( char infix[], char postfix[] ){
	/* create the stack and add left bracket
	 * My stack implimentation uses a single node as the 
	 * head node (called 'stack') which only points to the first 
	 * item of the stack and itself holds no data. if the stack is
	 * empty the head node's nextPtr field will be NULL. Otherwise it
	 * will maintain a link to the actual first node in the stack */
	StackNodePtr stack = malloc(sizeN);
	push(&stack, '(');
	
	//append the ')' to the end of the infix expression
	int inf;
	for (inf = 0; inf < 79; inf++){
		if (infix[inf] == '\0'){
			infix[inf] = ')';
			infix[inf+1] = '\0';
			break;
		}
	}
	
	//begin conversion
	inf = 0;
	int post = 0;
	
	//while stack isnt empty
	while (!isEmpty(stack) && inf < 80){
		//look at next character in postfix
		char c = infix[inf];
		
		//check if operator
		if (isOperator(c)){
			//character is an operator
			
			if (isOperator(c) == 5){
				/* operator is right bracket so pop all operators
				 * from stack onto postfix until hit left bracket */				
				while (isOperator(stackTop(stack)) != 4){
					postfix[post++] = pop(&stack);
				}
				
				//finally pop the left bracket
				pop(&stack);
				inf++;
				
			} else if (precedence(stackTop(stack), c) >= 0 && isOperator(stackTop(stack)) != 4){
				/* operator on stack is higher/equal precedence, 
				 * have to pop it */
				postfix[post++] = pop(&stack);
				
			} else {
				/* character is operator of lower precedence (or
				 * is left bracket), so push onto stack */
				push(&stack, c);
				inf++;
			}
		} else {
			//character is a digit, so put onto postfix
			postfix[post++] = c;
			inf++;
		}
	}
	
}
 
 /** returns the enumeration number of the character
  * if its not a character, will return 0 */
int isOperator( char c ){
	switch (c){
		case ('+'): return Add;
		case ('-'): return Subtract;
		case ('*'): return Multiply;
		case ('/'): return Divide;
		case ('^'): return Exponent;
		case ('%'): return Modulus;
		case ('('): return LeftBracket;
		case (')'): return RightBracket;
	}
	return 0;
}
 
/** uses isOperator to convert each character into an int based on their
 * precedence, and then returns the comparison */
int precedence( char operator1, char operator2 ){
	int o1 = isOperator(operator1);
	int o2 = isOperator(operator2);
	return o1 - o2;
} 
 
 
void push( StackNodePtr *topPtr, char value ){
	StackNodePtr stack = *topPtr;
	//get pointer to the first node (which will soon be the second)
	StackNodePtr temp = stack->nextPtr;
	//create new node
	stack->nextPtr = malloc(sizeN);
	stack->nextPtr->data = value;
	//add the rest of the stack to the end of the new node
	stack->nextPtr->nextPtr = temp;
}
 
char pop( StackNodePtr *topPtr ){
	StackNodePtr stack = *topPtr;
	if (isEmpty(stack)){
		return '\0';
	}
	//get the node to be deleted
	StackNodePtr temp = stack->nextPtr;
	//set the new top of the stack
	stack->nextPtr = temp->nextPtr;
	//get the data to return
	char pop = temp->data;
	//free the memory
	free(temp);
	return pop;
}
 
char stackTop( StackNodePtr topPtr ){
	if (topPtr->nextPtr == NULL) return '\0';
	return topPtr->nextPtr->data;
}
 
int isEmpty( StackNodePtr topPtr ){
	if (topPtr->nextPtr == NULL){
		return 1;
	}
	return 0;
}

int compute(char* infix){
	//allocate string (80 chars)
	char *postfix = malloc(80 * sizeof(char));
	
	//convert to postfix
	convertToPostfix(infix, postfix);
	
	//compute answer
	return computePostfix(postfix);
}
