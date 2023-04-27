#include "shell.h"

/**
 * cleanup - frees arguments and inputs
 * @args: Arguments used
 * @input: command inputs
 * Return: Nothing
 */

void cleanup(char **args, char *input)
{
free(args);
free(input);
}

/**
 * handle_sigint - handles signed integers
 * @sig: Integer variable
 * Return: Nothing
 */

void handle_sigint(int sig)
{
printf("%d\n", sig);
}
