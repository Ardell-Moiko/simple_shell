#include "main.h"

char *handle_errors_126(char **args);
char *handle_errors_127(char **args);

/**
 * handle_errors_126 - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */

char *handle_errors_126(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

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
	_mystrcat(error, ": ");
	_mystrcat(error, args[0]);
	_mystrcat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * handle_errors_127 - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *handle_errors_127(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _mystrlen(name) + _mystrlen(hist_str) + _mystrlen(args[0]) + 16;
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
	_mystrcat(error, ": not found\n");

	free(hist_str);
	return (error);
}
