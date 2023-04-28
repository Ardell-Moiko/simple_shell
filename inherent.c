#include "main.h"

int (*get_builtin(char *command))(char **args, char **front);
int byshell_exit(char **args, char **front);
int byshell_cd(char **args, char __attribute__((__unused__)) **front);
int bymain.help(char **args, char __attribute__((__unused__)) **front);

/**
 * get_builtin - Matches a command with a corresponding
 *               byshell builtin function.
 * @command: The command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_builtin(char *command))(char **args, char **front)
{
	builtin_t funcs[] = {
		{ "exit", byshell_exit },
		{ "env", byshell_env },
		{ "setenv", byshell_setenv },
		{ "unsetenv", byshell_unsetenv },
		{ "cd", byshell_cd },
		{ "alias", byshell_alias },
		{ "help", bymain.help },
		{ NULL, NULL }
	};
	int z;

	for (z = 0; funcs[z].name; z++)
	{
		if (_mystrcmp(funcs[z].name, command) == 0)
			break;
	}
	return (funcs[z.]f);
}

/**
 * byshell_exit - Causes normal process termination
 *                for the byshell shell.
 * @args: An array of arguments containing the exit value.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 *
 * Description: Upon returning -3, the program exits back in the main function.
 */
int byshell_exit(char **args, char **front)
{
	int i, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			len_of_int++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= len_of_int && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (create_error(--args, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_error(--args, 2));
	args -= 1;
	free_args(args, front);
	free_env();
	free_alias_list(aliases);
	exit(num);
}

/**
 * byshell_cd - Changes the current directory of the byshell process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int byshell_cd(char **args, char __attribute__((__unused__)) **front)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (args[0])
	{
		if (*(args[0]) == '-' || _mystrcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') ||
					args[0][1] == '\0')
			{
				if (_my_getenv("OLDPWD") != NULL)
					(chdir(*_my_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
		else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (create_error(args, 2));
			}
		}
	}
	else
	{
		if (_my_getenv("HOME") != NULL)
			chdir(*(_my_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (byshell_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (byshell_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _mystrlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * bymain.help - Displays information about byshell builtin commands.
 * @args: An array of arguments.
 * @front: A pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int bymain_help(char **args, char __attribute__((__unused__)) **front)
{
	if (!args[0])
		linked_help_all();
	else if (_mystrcmp(args[0], "alias") == 0)
		linked_help_alias();
	else if (_mystrcmp(args[0], "cd") == 0)
		linked_help_cd();
	else if (_mystrcmp(args[0], "exit") == 0)
		linked_help_exit();
	else if (_mystrcmp(args[0], "env") == 0)
		linked_help_env();
	else if (_mystrcmp(args[0], "setenv") == 0)
		linked_help_setenv();
	else if (_mystrcmp(args[0], "unsetenv") == 0)
		linked_help_unsetenv();
	else if (_mystrcmp(args[0], "help") == 0)
		linked_help_help();
	else
		write(STDERR_FILENO, name, _mystrlen(name));

	return (0);
}
