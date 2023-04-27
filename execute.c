#include "shell.h"

/**
 *execute - execute the commands in the program
 *@args: Arguments to be executed
 *return: 1
 */

int execute(char **args)
{
	int builtin_status = check_builtin(args);
	char *path_env = getenv("PATH");
	char *path = strtok(path_env, ":");

	setenv("PATH", "/usr:/bin", 1);

	if (path_env == NULL)
	{
		perror("getenv failed");
		exit(EXIT_FAILURE);
	}

	while (path != NULL)
	{
		char *command_path = malloc(strlen(path) + strlen(args[0]) + 2);

		if (command_path == NULL)
		{
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
		sprintf(command_path, "%s/%s", path, args[0]);

		if (access(command_path, X_OK) == 0)
		{
			pid_t pid = fork();

			if (pid == -1)
			{
				perror("fork failed");
				exit(EXIT_FAILURE);

			}
			else if (pid == 0)
			{
				execvp(command_path, args);
				perror("execvp failed");
				exit(EXIT_FAILURE);
			} else
			{
				int status;

				if (waitpid(pid, &status, 0) == -1)
				{
					perror("waitpid failed");
					exit(EXIT_FAILURE);
				}
				args[0] = NULL;
				return (WEXITSTATUS(status));
			}
		}
		free(command_path);
		path = strtok(NULL, ":");
	}
	if (builtin_status != -1)
	{
		return (builtin_status);
	}
	if (args[0] != NULL)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
	}

	return (1);
}

