#include "shell.h"

/**
 * execute_command - Executes a command with arguments
 *
 *@datash: Data relevant to the shell
 * Return: 0 on failure, 1 on success
 */
int execute_command(data_shell *datash)
{
	int status;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		printf("Fork error");
		return (0);
	}

	if (pid == 0)
	{
		if (execve(datash->args[0], datash->args, datash->_environ) == -1)
		{
			printf("Execution error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			return (1);
	}

	return (0);
}

/**
 * handle_logical_operators - Handles the shell logical operators: && and ||
 *
 * @datash: Data relevant to the shell
 * Return: 0 otherwise, 1 if the command is executed
 */
int handle_logical_operators(data_shell *datash)
{
	if (datash->args[datash->index + 1] != NULL)
	{
		if (datash->logical_operator == AND)
		{
			if (!execute_command(datash))
				return (0);
		}
		else if (datash->logical_operator == OR)
		{
			if (execute_command(datash))
				return (0);
		}
	}

	return (1);
}

/**
 * execute_line - Executes a line of commands
 *
 * @datash: Data relevant to the shell
 * Return: 0 on failure, 1 on success
 */
int execute_line(data_shell *datash)
{
	int i;

	if (datash->args[0] == NULL)
		return (1);
	for (i = 0; i < datash->num_logical_operators; i++)
	{
		datash->logical_operator = datash->logical_operators[i];

		if (!handle_logical_operators(datash))
			return (0);

		datash->index++;
	}

	if (!execute_command(datash))
		return (0);

	return (1);
}

/**
 * main - Entry point of the shell program
 *
 * Return: 0 success
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	data_shell datash;

	signal(SIGINT, SIG_IGN);

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (feof(stdin))
				break;
			perror("getline");
			exit(EXIT_FAILURE);
		}

		if (parse_line(line, &datash))
		{
			execute_line(&datash);
			free_data(&datash);
		}
		else
			fprintf(stderr, "Syntax error\n");
	}

	free(line);
	exit(EXIT_SUCCESS);
}
