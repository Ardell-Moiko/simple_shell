#include "main.h"

char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int arguments_handler(int *exe_ret);
int argument_check(char **args);

/**
 * get_args - Takes a command from standard input.
 * @line: A buffer to store the command taken.
 * @exe_ret: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *get_args(char *line, int *exe_ret)
{
	ssize_t rd;
	size_t i = 0;
	char *prompt = "$ ";

	if (line)
		free(line);

	rd = _getline(&line, &i, STDIN_FILENO);
	if (rd == -1)
		return (NULL);
	if (rd == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exe_ret));
	}

	line[rd - 1] = '\0';
	replace_var(&line, exe_ret);
	line_handler(&line, rd);

	return (line);
}

/**
 * call_args - Partitions operators from commands and calls them.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int call_args(char **args, char **front, int *exe_ret)
{
	int retn, i;

	if (!args[0])
		return (*exe_ret);
	for (i = 0; args[i]; i++)
	{
		if (_mystrncmp(args[i], "||", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = alias_replace(args);
			retn = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
					free(args[i]);
				return (retn);
			}
		}
		else if (_mystrncmp(args[i], "&&", 2) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			args = alias_replace(args);
			retn = run_args(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++i];
				i = 0;
			}
			else
			{
				for (i++; args[i]; i++)
					free(args[i]);
				return (retn);
			}
		}
	}
	args = alias_replace(args);
	retn = run_args(args, front, exe_ret);
	return (retn);
}

/**
 * run_args - Calls the execution of a command.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int run_args(char **args, char **front, int *exe_ret)
{
	int ret, i;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = execute(args, front);
		ret = *exe_ret;
	}

	hist++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}

/**
 * arguments_handler - Gets, calls, and runs the execution of a command.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int arguments_handler(int *exe_ret)
{
	int ret = 0, i;
	char **args, *ln = NULL, **frnt;

	ln = get_args(ln, exe_ret);
	if (!ln)
		return (END_OF_FILE);

	args = _mystrtok(ln, " ");
	free(ln);
	if (!args)
		return (ret);
	if (argument_check(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	frnt = args;

	for (i = 0; args[i]; i++)
	{
		if (_mystrncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = call_args(args, frnt, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}
	if (args)
		ret = call_args(args, frnt, exe_ret);

	free(frnt);
	return (ret);
}

/**
 * argument_check - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int argument_check(char **args)
{
	char *curr, *nxt;
	size_t i;

	for (i = 0; args[i]; i++)
	{
		curr = args[i];
		if (curr[0] == ';' || curr[0] == '&' || curr[0] == '|')
		{
			if (i == 0 || curr[1] == ';')
				return (create_error(&args[i], 2));
			nxt = args[i + 1];
			if (nxt && (nxt[0] == ';' || nxt[0] == '&' || nxt[0] == '|'))
				return (create_error(&args[i + 1], 2));
		}
	}
	return (0);
}

