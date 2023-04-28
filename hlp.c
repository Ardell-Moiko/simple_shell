#include "main.h"

void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void replace_var(char **args, int *exe_ret);

/**
 * free_args - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the beginning of args.
 */

void free_args(char **args, char **front)
{
	size_t k;

	for (k = 0; args[k] || args[k + 1]; k++)
		free(args[k]);

	free(front);
}

/**
 * get_pid - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */

char *get_pid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - Gets the value corresponding to an environmental variable.
 * @beginning: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_mystrncat(var, beginning, len);

	var_addr = _my_getenv(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_mystrlen(temp) + 1);
		if (replacement)
			_mystrcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * replace_var - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void replace_var(char **line, int *exe_ret)
{
	int m, k = 0, len;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (m = 0; old_line[m]; m++)
	{
		if (old_line[m] == '$' && old_line[m + 1] &&
				old_line[m + 1] != ' ')
		{
			if (old_line[m + 1] == '$')
			{
				replacement = get_pid();
				k = m + 2;
			}
			else if (old_line[m + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				k = m + 2;
			}
			else if (old_line[m + 1])
			{
				/* extract the variable name to search for */
				for (k = m + 1; old_line[k] &&
						old_line[k] != '$' &&
						old_line[k] != ' '; k++)
					;
				len = k - (m + 1);
				replacement = get_env_value(&old_line[m + 1], len);
			}
			new_line = malloc(m + _mystrlen(replacement)
					+ _mystrlen(&old_line[k]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_mystrncat(new_line, old_line, m);
			if (replacement)
			{
				_mystrcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_mystrcat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			m = -1;
		}
	}
}
