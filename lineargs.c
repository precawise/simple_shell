#include "shell.h"

/**
 * Global Variables
 */
int last_exit_status = 0;
pid_t shell_pid;

/**
 * Function to replace variables in the command line
 */
void replace_variables(char *line)
{
	/* Replace $? with the last exit status */
	char exit_status[10];
	snprintf(exit_status, sizeof(exit_status), "%d", last_exit_status);
	char *pos = strstr(line, "$?");
	while (pos != NULL)
	{
		size_t len = strlen(line) - strlen(pos);
		memmove(pos, exit_status, strlen(exit_status));
		memmove(pos + strlen(exit_status), pos + 2, strlen(pos + 2) + 1);
		pos = strstr(line + len + strlen(exit_status), "$?");
	}

	/* Replace $$ with the shell process ID */
	char pid[10];
	snprintf(pid, sizeof(pid), "%d", shell_pid);
	pos = strstr(line, "$$");
	while (pos != NULL)
	{
		size_t len = strlen(line) - strlen(pos);
		memmove(pos, pid, strlen(pid));
		memmove(pos + strlen(pid), pos + 2, strlen(pos + 2) + 1);
		pos = strstr(line + len + strlen(pid), "$$");
	}
}

/**
 * Function to execute a command
 */
void execute_command(char *command)
{
	/* Execute the command */
	int status = system(command);

	/* Store the exit status */
	last_exit_status = WEXITSTATUS(status);
}

/**
 * Main function
 */
int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		FILE *file = fopen(argv[1], "r");
		if (file == NULL)
		{
			fprintf(stderr, "Error opening file: %s\n", argv[1]);
			exit(EXIT_FAILURE);
		}

		char *line = NULL;
		size_t len = 0;
		ssize_t nread;

		/* Get the shell process ID */
		shell_pid = getpid();

		while ((nread = getline(&line, &len, file)) != -1)
		{
			/* Remove newline character */
			if (line[nread - 1] == '\n')
				line[nread - 1] = '\0';

			/* Replace variables in the command */
			replace_variables(line);

			/* Execute the command */
			execute_command(line);
		}

		free(line);
		fclose(file);
	}
	else
	{
		/* Interactive mode */
		char *line = NULL;
		size_t len = 0;
		ssize_t nread;

		/* Get the shell process ID */
		shell_pid = getpid();

		while (1)
		{
			printf("$ ");
			nread = getline(&line, &len, stdin);
			if (nread == -1)
			{
				if (feof(stdin))
					break;
				perror("getline");
				exit(EXIT_FAILURE);
			}

			/* Remove newline character */
			if (line[nread - 1] == '\n')
				line[nread - 1] = '\0';

			/* Replace variables in the command */
			replace_variables(line);

			/* Execute the command */
			execute_command(line);
		}

		free(line);
	}

	return 0;
}
