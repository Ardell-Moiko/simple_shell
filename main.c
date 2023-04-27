#include "shell.h"
11;rgb:0000/0000/0000
/**
 * main - main function
 * @argc: Argument count
 * @argv: Value of argument
 * Return: EXIT_SUCCESS
 */

int main(int argc, char *argv[])
{
char *input;
char **args;
bool should_continue = true;

setenv("PATH", "/bin:/usr", 1);
signal(SIGINT, handle_sigint);
signal(SIGTERM, handle_sigint);

if (argc > 1)
{
FILE *file = fopen(argv[1], "r");
if (!file)
{
perror("fopen failed");
exit(EXIT_FAILURE);
}
while ((input = get_input_file(file)) != NULL)
{
args = parse_input(input);

if (args[0] == NULL)
{
continue;
}
if (strcmp(args[0], "exit") == 0)
{
should_continue = false;
break;
}
else if (strcmp(args[0], "cd") == 0)
{
if (args[1] == NULL)
{
chdir(getenv("HOME"));
}
else
{
if (chdir(args[1]) == -1)
{
printf("cd: %s: %s\n", args[1], strerror(errno));
}
}
}
else
{
if (execute(args) == -1)
{
printf("%s: %s\n", args[0], strerror(errno));
}
}
cleanup(args, input);
}
fclose(file);
}
else
{
do {
printf("$ ");
fflush(stdout);

input = get_input();
args = parse_input(input);

if (args[0] == NULL)
{
cleanup(args, input);
continue;
}

if (strcmp(args[0], "exit") == 0)
{
should_continue = false;
}
else if (strcmp(args[0], "cd") == 0)
{
if (args[1] == NULL)
{
chdir(getenv("HOME"));
}
else
{
if (chdir(args[1]) == -1)
{
printf("cd: %s: %s\n", args[1], strerror(errno));
}
}
}
else
{
if (execute(args) == -1)
{
printf("%s: %s\n", args[0], strerror(errno));
}
}
cleanup(args, input);

}
while (should_continue)
;
}
return (EXIT_SUCCESS);
}
