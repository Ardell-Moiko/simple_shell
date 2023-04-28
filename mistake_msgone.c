#include "main.h"

char *handle_errors_env(char **args);
char *handle_errors_1(char **args);
char *handle_errors_2_exit(char **args);
char *handle_errors_2_cd(char **args);
char *handle_errors_2_syntax(char **args);
/**
 * handle_errors_env - Creates an error message for byshell_env errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *handle_errors_env(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	args--;
	len = _mystrlen(name) + _mystrlen(hist_str) + _mystrlen(args[0]) + 45;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_mystrcpy(error, name);
	_mystrcat(error, ": ");
	_mystrcat(error, hist_str);
	_mystrcat(error, ": ");
	_mystrcat(error, args[0]);
	_mystrcat(error, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (error);
}

/**
 * handle_errors_1 - Creates an error message for byshell_alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *handle_errors_1(char **args)
{
	char *error;
	int len;

	len = _mystrlen(name) + _mystrlen(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	_mystrcpy(error, "alias: ");
	_mystrcat(error, args[0]);
	_mystrcat(error, " not found\n");

	return (error);
}

/**
 * handle_errors_2_exit - Creates an error message for byshell_exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *handle_errors_2_exit(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _mystrlen(name) + _mystrlen(hist_str) + _mystrlen(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_mystrcpy(error, name);
	_mystrcat(error, ": ");
	_mystrcat(error, hist_str);
	_mystrcat(error, ": exit: Illegal number: ");
	_mystrcat(error, args[0]);
	_mystrcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * handle_errors_2_cd - Creates an error message for byshell_cd errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *handle_errors_2_cd(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	len = _mystrlen(name) + _mystrlen(hist_str) + _mystrlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_mystrcpy(error, name);
	_mystrcat(error, ": ");
	_mystrcat(error, hist_str);
	if (args[0][0] == '-')
		_mystrcat(error, ": cd: Illegal option ");
	else
		_mystrcat(error, ": cd: can't cd to ");
	_mystrcat(error, args[0]);
	_mystrcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * handle_errors_2_syntax - Creates an error message for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *handle_errors_2_syntax(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _mystrlen(name) + _mystrlen(hist_str) + _mystrlen(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_mystrcpy(error, name);
	_mystrcat(error, ": ");
	_mystrcat(error, hist_str);
	_mystrcat(error, ": Syntax error: \"");
	_mystrcat(error, args[0]);
	_mystrcat(error, "\" unexpected\n");

	free(hist_str);
	return (error);
}
