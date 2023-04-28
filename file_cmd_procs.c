#include "main.h"

int cant_open(char *file_path);
int file_process_comnds(char *file_path, int *exe_ret);

/**
 * cant_open - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */

int cant_open(char *file_path)
{
	int len;
	char *error, *strn_hist;

	strn_hist = _itoa(hist);
	if (!strn_hist)
		return (127);

	len = _mystrlen(name) + _mystrlen(strn_hist) + _mystrlen(file_path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(strn_hist);
		return (127);
	}

	_mystrcpy(error, name);
	_mystrcat(error, ": ");
	_mystrcat(error, strn_hist);
	_mystrcat(error, ": Can't open ");
	_mystrcat(error, file_path);
	_mystrcat(error, "\n");

	free(strn_hist);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * file_process_comnds - Takes a file and attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exe_ret: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int file_process_comnds(char *file_path, int *exe_ret)
{
	ssize_t file, b_read, i;
	unsigned int line_size = 0;
	unsigned int o_size = 120;
	char *line, **args, **frnt;
	char buff[120];
	int rtn;

	hist = 0;
	file = open(file_path, O_RDONLY);
	if (file == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * o_size);
	if (!line)
		return (-1);
	do {
		b_read = read(file, buff, 119);
		if (b_read == 0 && line_size == 0)
			return (*exe_ret);
		buff[b_read] = '\0';
		line_size += b_read;
		line = _myrealloc(line, o_size, line_size);
		_mystrcat(line, buff);
		o_size = line_size;
	} while (b_read);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < line_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < line_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	replace_var(&line, exe_ret);
	line_handler(&line, line_size);
	args = _mystrtok(line, " ");
	free(line);
	if (!args)
		return (0);
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
			rtn = call_args(args, frnt, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}

	rtn = call_args(args, frnt, exe_ret);

	free(frnt);
	return (rtn);
}

