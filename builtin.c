#include "shell.h"

/**
 * myExit - Terminate the shell
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Exit status (0) if info.argv[0] != "exit"
 */
int myExit(info_t *info)
{
	int exitCheck;

	if (info->argv[1])  /* Check if there is an exit argument */
	{
		exitCheck = customAtoi(info->argv[1]);
		if (exitCheck == -1)
		{
			info->status = 2;
			printError(info, "Illegal number: ");
			_printString(info->argv[1]);
			_printChar('\n');
			return (1);
		}
		info->errorNumber = customAtoi(info->argv[1]);
		return (-2);
	}
	info->errorNumber = (-1);
	return (-2);
}

/**
 * myCD - Change the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0
 */
int myCD(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdirRet;

	s = getCurrentWorkingDirectory(buffer, 1024);
	if (!s)
		_printString("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = getEnvironmentVariable(info, "HOME=");
		if (!dir)
			chdirRet = /* TODO: what should this be? */
				changeDirectory((dir = getEnvironmentVariable(info, "PWD=")) ? dir : "/");
		else
			chdirRet = changeDirectory(dir);
	}
	else if (customStrcmp(info->argv[1], "-") == 0)
	{
		if (!getEnvironmentVariable(info, "OLDPWD="))
		{
			_printString(s);
			_printChar('\n');
			return (1);
		}
		_printString(getEnvironmentVariable(info, "OLDPWD=")), _putchar('\n');
		chdirRet = /* TODO: what should this be? */
		changeDirectory((dir = getEnvironmentVariable(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdirRet = changeDirectory(info->argv[1]);
	if (chdirRet == -1)
	{
		printError(info, "can't cd to ");
		_printString(info->argv[1]), _putchar('\n');
	}
	else
	{
		setEnvironmentVariable(info, "OLDPWD", getEnvironmentVariable(info, "PWD="));
		setEnvironmentVariable(info, "PWD", s);
	}
	return (0);
}

/**
 * myHelp - Display help information
 * @info: Structure containing potential arguments. Used to maintain
 *         constant function prototype.
 * Return: Always 0
 */
int myHelp(info_t *info)
{
	char **argArray;

	argArray = info->argv;
	_printString("help call works. Function not yet implemented \n");
	if (0)
		_printString(*argArray); /* Temporary workaround for unused warning */
	return (0);
}
