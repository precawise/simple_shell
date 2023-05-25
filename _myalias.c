#include "shell.h"

/**
 * _myalias - Implementation of the 'alias' built-in command
 * @info: Pointer to info_t struct
 *
 * Return: Always returns 0
 */
int _myalias(info_t *info)
{
	unsigned int i;

	if (info->alias == NULL)
	{
		_eputs("No aliases set\n");
		return (0);
	}

	for (i = 0; info->alias[i].str != NULL; i++)
		printf("%s='%s'\n", info->alias[i].str, info->alias[i].next->str);

	return (0);
}
