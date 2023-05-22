#include "shell.h"

/**
 * change_directory - Changes the current directory of process
 *
 * @datash: data relevant (environ)
 *
 * Return: 0 on success, -1 on failure.
 */
void change_directory(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, datash);
	dir = datash->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, datash);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_string(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok(NULL, "\0"));

	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_string(cp_strtok_pwd);
	}

	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, datash);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datash);
	}
	datash->status = 0;
	free(cp_pwd);
}

/**
 * change_directory_to - changes to a directory
 * given by a user
 *
 * @datash: data relevant(directories)
 * Return: 0 on success, -1 on failure
 */
void change_directory_to(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dir, cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = datash->args[1];
	if (chdir(dir) == -1)
	{
		get_error(datash, 2);
		return;
	}

	cp_pwd =  _strdup(pwd);
	set_env("OLDPWD", cp_pwd, datash);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, datash);

	free(cp_pwd);
	free(cp_dir);

	datash->status = 0;

	chdir(dir);
}

/**
 * change_directory_previous - changes to previous directory
 *
 * @datash: data relevant (environ)
 *
 * Return: 0 on success, -1 on failure
 */
void change_directory_previous(data_shell *datash)
{
	char *p_oldpwd = _getenv("OLDPWD", datash->_environ);
	char *cp_oldpwd = p_oldpwd ? _strdup(p_oldpwd) : NULL;

	if (cp_oldpwd == NULL || chdir(cp_oldpwd) == -1)
	{
		get_error(datash, 2);
		free(cp_oldpwd);
		return;
	}

	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));

	set_env("OLDPWD", _strdup(pwd), datash);
	set_env("PWD", cp_oldpwd, datash);

	write(STDOUT_FILENO, cp_oldpwd, _strlen(cp_oldpwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_oldpwd);

	datash->status = 0;

	chdir(pwd);
}

/**
 * change_directory_to_home - changes to home directory
 *
 * @datash: data relevant (environ)
 * Return: -1 on failure, 0 on success
 */
void change_directory_to_home(data_shell *datash)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", datash->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, datash);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(datash, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, datash);
	set_env("PWD", home, datash);
	free(p_pwd);
	datash->status = 0;
}
