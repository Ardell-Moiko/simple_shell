#include "shell.h"
/**
 * get_input - get user inputs
 *
 * Return: buffer
 * A character buffer containing the input read from the standard input stream.
 */

char *get_input(void)
{
	char *buffer = malloc(BUFFER_SIZE);

	if (buffer == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}

	if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
	{
		printf("\n");
		exit(EXIT_SUCCESS);
	}

	return (buffer);
}

/**
 *get_input_file - get user inputs
 *@file: get input file
 *Return: NULL
 */

char *get_input_file(FILE *file)
{
	static char buffer[1024];

	if (fgets(buffer, sizeof(buffer), file) != NULL)
	{
		buffer[strcspn(buffer, "\n")] = '\0';
		return (buffer);
	}
	return (NULL);
}
