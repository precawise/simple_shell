#include "shell.h"

#define MAX_COMMAND_LENGTH 1000

/**
 * run_shell_commands - Executes the shell commands from the specified file.
 * @filename: The name of the file containing the commands.
 */
void run_shell_commands(const char *filename)
{
	FILE *file = fopen(filename, "r");

	if (file == NULL)
	{
		printf("File '%s' not found.\n", filename);
		exit(1);
	}

	char command[MAX_COMMAND_LENGTH];

	while (fgets(command, sizeof(command), file))
	{
		command[strcspn(command, "\n")] = '\0';

		system(command);
	}

	fclose(file);
}

/**
 * main - The entry point of the simple shell program.
 * @argc: The number of command-line arguments.
 * @argv: An array of command-line arguments.
 *
 * Return: The exit status of the program.
 */
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: simple_shell [filename]\n");
		return (1);
	}

	const char *filename = argv[1];

	run_shell_commands(filename);

	return (0);
}
