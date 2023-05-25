#include <stdio.h>

/**
 * add -  Adds two integers
 * @a: First integer.
 * @b: Second integer
 *
 * Return: Sum of the two integers
 */
int add(int a, int b)
{
	return (a + b);
}

/**
 * multiply - Multiplies two integers
 * @a: First integer
 * @b: Second integer
 *
 * Return: Product of the two integers
 */
int multiply(int a, int b)
{
	return (a * b);
}

/**
 * print_result - Prins the result of an operation
 * @operation: Name of operation
 * @result: Result of the operation
 */
void print_result(const char *operation, int result)
{
	printf("The result is %s is: %d\n", operation, result);
}
