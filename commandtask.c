#include "shell.h"

/**
 * change_directory - Changes current directory of the process.
 *
 * @path: The directory path to change to.
 * Return: 0 on success, -1 on failure.
 */
int change_directory(const char *path)
{
	int result;

	result = chdir(path);
	if (result != 0)
	{
		perror("cd");
		return (-1);
	}
	return (0);
}

/**
 * execute_command - Execute a single command.
 *
 * @command: The command to execute.
 * Return: 0 on success, -1 on failure.
 */
int execute_command(const char *command)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		execlp(command, command, NULL);
		perror(command);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	else
	{
		/* Parent process */
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (0);
}

/**
 * execute_commands - Executes multiple commands separated by ','.
 *
 * @commands: The commands to execute.
 * Return: 0 on success, -1 on failure.
 */
int execute_commands(const char *commands)
{
	char *token;
	char *copy;
	int status = 0;

	copy = strdup(commands);
	if (copy == NULL)
	{
		perror("strdup");
		return (-1);
	}

	token = strtok(copy, ",");
	while (token != NULL)
	{
		status = execute_command(token);
		token = strtok(NULL, ",");
	}

	free(copy);
	return (status);
}

/**
 * main - Entry point of simple shell program.
 *
 * Return: 0.
 */
int main(void)
{
	char command[256];

	while (1)
	{
		printf("> ");
		fflush(stdout);

		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		if (command[strlen(command) - 1] == '\n')
		{
			command[strlen(command) - 1] = '\0';
		}

		execute_commands(command);
	}

	return (0);
}
