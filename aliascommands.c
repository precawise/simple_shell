#include "shell.h"

/**
 * print_aliases - Prints all aliases in the form name='value'
 *
 * @aliases: The aliases data structure
 */
void print_aliases(alias_t *aliases)
{
	alias_t *current = aliases;

	while (current != NULL)
	{
		printf("%s='%s'\n", current->name, current->value);
		current = current->next;
	}
}

/**
 * print_alias - Prints the alias with the given name
 *
 * @aliases: Aliases data structure
 * @name: Name of the alias to print
 */
void print_alias(alias_t *aliases, char *name)
{
	allias_t *current = aliases;

	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
		{
			printf("%S='%s'\n", current->name, current->value);
			break;
		}
		current = current->next;
	}
}
/**
 * add_alias - Adds an alias with the given name and value
 *
 * @aliases: Aliases data structure
 * @name: Name of alias
 * @value: Value of the alias
 */
void add_alias(alias_t **aliases, char *name, char *value)
{
	alias_t *new_alias = malloc(sizeof(alias_t));
	alias_t *current = *aliases;

	if (new_allias == NULL)
	{
		fprintf(stderr, "Memory allocation error\n");
		return;
	}

	new_alias->name = strdup(name);
	new_alias->value = strdup(value);
	new_alias->next = NULL;

	if (current == NULL)
	{
		*aliases = new_alias;
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new_alias;
	}
}
/**
 * set_alias - Sets value of an existing alias
 *
 * @aliases: Aliases data structure
 * @name: Name of the alias
 * @value: New value of the alias
 */
void set_alias(alias_t *aliases, char *name, char *value)
{
	alias_t *current = aliases;

	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
		{
			free(current->value);
			current->value = strdup(value);
			break;
		}
		current = current->next;
	}
}
/**
 * alias_builtin - Implements the alias built-in command
 *
 * @datash: Data relevant to the shell
 */
void alias_builtin(data_shell *datash)
{
	int i = 1;
	char *name, *value;
	char *arg = datash->args[i];

	if (arg == NULL)
	{
		print_aliases(datash->aliases);
		return;
	}

	while (arg != NULL)
	{
		value = strchr(arg, '=');
		if (value != NULL)
		{
			*value = '\0';
			value++;
			if (*value == '\0')
				value = NULL;
		}

		if (value == NULL)
		{
			print_alias(datash->aliases, arg);
		}
		else
		{
			name = arg;
			add_alias(&(datash->aliases), name, value);
		}

		i++;
		arg = datash->args[i];
	}
}

/**
 * main - Entry point of the shell program
 *
 * Return: 0 on success
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
			printf("getline");
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
