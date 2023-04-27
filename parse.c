#include "shell.h"

/**
 *parse_input - get user inputs
 *@input: User input
 *Return: args
 */

char **parse_input(char *input)
{
	char **args = malloc(sizeof(char *) * MAX_ARGS);
	int i = 0;
	char *token = strtok(input, " \n");

	if (args == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}

	while (token != NULL && i < MAX_ARGS - 1)
	{
		if (token[0] == '$')
		{
			char *var = &token[1];
			char *val = getenv(var);

			if (val == NULL)
			{
				printf("%s: Undefined variable\n", var);
				return (NULL);
			}
			args[i] = strdup(val);
		} else
		{
			args[i] = strdup(token);
		}
		if (args[i] == NULL)
		{
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
		token = strtok(NULL, " \n");
		i++;
	}
	args[i] = NULL;

	return (args);
}
