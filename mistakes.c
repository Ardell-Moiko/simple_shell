#include "main.h"

int num_len(int num);
char *_itoa(int num);
int create_error(char **args, int err);

/**
 * num_len - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int num_len(int num)
{
	unsigned int number1;
	int len = 1;

	if (num < 0)
	{
		len++;
		number1 = num * -1;
	}
	else
	{
		number1 = num;
	}
	while (number1 > 9)
	{
		len++;
		number1 /= 10;
	}

	return (len);
}

/**
 * _itoa - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *_itoa(int num)
{
	char *buffer;
	int len = num_len(num);
	unsigned int numb1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		numb1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		numb1 = num;
	}

	len--;
	do {
		buffer[len] = (numb1 % 10) + '0';
		numb1 /= 10;
		len--;
	} while (numb1 > 0);

	return (buffer);
}


/**
 * create_error - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
int create_error(char **args, int err)
{
	char *error;

	switch (err)
	{
		case -1:
			error = handle_errors_env(args);
			break;
		case 1:
			error = handle_errors_1(args);
			break;
		case 2:
			if (*(args[0]) == 'e')
				error = handle_errors_2_exit(++args);
			else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
				error = handle_errors_2_syntax(args);
			else
				error = handle_errors_2_cd(args);
			break;
		case 126:
			error = handle_errors_126(args);
			break;
		case 127:
			error = handle_errors_127(args);
			break;
	}
	write(STDERR_FILENO, error, _mystrlen(error));

	if (error)
		free(error);
	return (err);

}
