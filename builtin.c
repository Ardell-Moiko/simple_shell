#include "shell.h"

/**
 * check_builtin - Checks for builtin commands
 * @args: Arguments to be executed
 * Return: -1
 */

int check_builtin(char **args)
{
if (strcmp(args[0], "cd") == 0)
{
if (args[1] == NULL)
{
fprintf(stderr, "cd: expected argument to \"cd\"\n");
}
else
{
if (chdir(args[1]) != 0)
{
perror("chdir failed");
}
}
return (1);
}
else if (strcmp(args[0], "exit") == 0)
{
return (0);
}
return (-1);
}
