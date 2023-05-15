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

/**
 * main - Entry point of program
 *
 * Return: 0 on success
 */
int main(void)
{
	int num2 = 10;
	int num3 = 5;
	int sum, product;

	sum = add(num2, num3);
	product = multiply(num2, num3);

	print_result("addition", sum);
	print_result("multiplication", product);

	return (0);
}
