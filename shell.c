#include "main.h"

void handle_sigint(int sig);
int execute(char **args, char **front);

/**
 * handle_sigint - a new prompt output upon a signal.
 * @sig: The signal.
 */
void handle_sigint(int sig)
{
	char *new_prmt = "\n$ ";

	(void)sig;
	signal(SIGINT, handle_sigint);
	write(STDIN_FILENO, new_prmt, 3);
}

/**
 * execute - Executes a command in a child process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */
int execute(char **args, char **front)
{
	pid_t child_pid;
	char *cmd = args[0];
	int stat, flag = 0, retrn = 0;

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flag = 1;
		cmd = g_locate(cmd);
	}

	if (!cmd || (access(cmd, F_OK) == -1))
	{
		if (errno == EACCES)
			retrn = (create_error(args, 126));
		else
			retrn = (create_error(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(cmd);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(cmd, args, environ);
			if (errno == EACCES)
				retrn = (create_error(args, 126));
			free_env();
			free_args(args, front);
			free_alias_list(aliases);
			_exit(retrn);
		}
		else
		{
			wait(&stat);
			retrn = WEXITSTATUS(stat);
		}
	}
	if (flag)
		free(cmd);
	return (retrn);
}

/**
 * main - Imitates a UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *exe_ret = &retn;
	char *prompt = "$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, handle_sigint);

	*exe_ret = 0;
	environ = copy_env();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = file_process_comnds(argv[1], exe_ret);
		free_env();
		free_alias_list(aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = arguments_handler(exe_ret);
		free_env();
		free_alias_list(aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = arguments_handler(exe_ret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			free_env();
			free_alias_list(aliases);
			exit(*exe_ret);
		}
	}

	free_env();
	free_alias_list(aliases);
	return (*exe_ret);
}

