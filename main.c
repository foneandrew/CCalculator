#include <stdio.h>
#include <stdlib.h>
#include "infix.h"

/**program to bring together the (modified) parts from a C Lab project
 * from NWEN2421 into a single program. I modified the original parts
 * to not print the stack out as it works, and to remove the main
 * methods and rename some other methods to avoid conflicts.
 * mostly this is just an excersise to see if i could link several c 
 * programs together and how to use a super basic makefile
 */
int main(void){
	//allocate strings (80 chars each)
	char *infix = malloc(80 * sizeof(char));
	
	/* get the infix expression from user.
	 * expects the expression to be in a 
	 * valid format (doesnt check validity)*/
	printf("Enter the expression to evaluate (79 chars max):\n");
	scanf("%s", infix);
	
	//set last char to \0 for safety
	infix[78] = '\0';
	
	//print the entered expression
	//printf("\n%s\n", infix);
	
	//print the answer
	printf("=%d\n\n", compute(infix));
	
	return 0;
}
