#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000
#define UNDERFLOW_INT -32767

typedef enum
{
	NO = 0,
	YES = 1,
} BOOL;


BOOL isStackFull (int tos)
{
	if (tos == SIZE - 1)
		return YES;
	return NO;
}

BOOL isStackEmpty (int tos)
{
	if (tos == -1)
		return YES;
	return NO;
}

void push (int *stack, int item, int *tos)
{
	if (*tos == SIZE - 1)
		return;
	(*tos) += 1;
	*(stack + (*tos)) = item;
}

int pop (int *stack, int *tos) {
	if (*tos == -1)
		return UNDERFLOW_INT;
	return *(stack + ((*tos)--));
}


int opResult (char op, int a, int b)
{
	switch (op)
	  {
		case '+': return a+b;
		case '-': return a-b;
		case '*': return a*b;
		case '/': return (int)(a/b);
		  //case '^': return (int)pow(a, b);
		default : return 0;
	}
}



int indexOf (char character, char *string)
{
	char *ptr = strchr(string, character);
	if (ptr)
		return (int)(ptr - string);
	return -1;
}


BOOL isOperator (char op)
{
	if (indexOf(op, "+-*/") != -1)
		return YES;
	return NO;
}


BOOL isNumber (char op)
{
	if (op >= '0' && op <= '9')
		return YES;
	return NO;
}

BOOL isAlpha (char op)
{
	if ((op >= 'A' && op <= 'Z') || (op >= 'a' && op <= 'z'))
		return YES;
	return NO;
}


int numeral (char character)
{
	return (int)(character - 48);
}

int postfixEval (char * exp)
{
	
	int tos = -1;
	int *stack = (int *)calloc(SIZE, sizeof(int));
	int l = (int)strlen(exp), i;
	
	for (i = 0; i < l; ++i)
	  {
		char z = *(exp + i);
		if (isNumber(z))
			push(stack, numeral(z), &tos);
		else if (isAlpha(z))
		  {
			int numz;
			printf("\n\tEnter the value of '%c': ", z);
			scanf("%d", &numz);
			push(stack, numz, &tos);
		}
		else if (isOperator(z))
		  {
			int b = pop(stack, &tos);
			int a = pop(stack, &tos);
			push(stack, opResult(z, a, b), &tos);
		}
		else
			return UNDERFLOW_INT;
	}
	if (tos == 0)
		return *stack;
	return UNDERFLOW_INT;
}

int main()
{
	
	char *string = (char *)calloc(SIZE, sizeof(char));
	
	printf("Enter postfix expression : ");
	scanf("%s", string);
	
	int result;
	result = postfixEval(string);
	
	if (result == UNDERFLOW_INT)
	  {
		printf("Invalid");
		exit(6);
	}
	
	printf("Result = %d\n", result);
	
	return 0;
}
