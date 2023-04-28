#include "main.h"

char *fill_path_dir(char *path);
list_t *dir_path(char *path);

/**
 * g_locate - Locates a command in the PATH.
 * @command: The command to locate.
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Otherwise - the full pathname of the command.
 */
char *g_locate(char *command)
{
	char **path, *tmp;
	list_t *dirs, *hd;
	struct stat st;

	path = _my_getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = dir_path(*path + 5);
	hd = dirs;

	while (dirs)
	{
		tmp = malloc(_mystrlen(dirs->dir) + _mystrlen(command) + 2);
		if (!tmp)
			return (NULL);

		_mystrcpy(tmp, dirs->dir);
		_mystrcat(tmp, "/");
		_mystrcat(tmp, command);

		if (stat(tmp, &st) == 0)
		{
			free_list(hd);
			return (tmp);
		}

		dirs = dirs->next;
		free(tmp);
	}

	free_list(hd);

	return (NULL);
}

/**
 * fill_path_dir - Copies path but also replaces leading/sandwiched/trailing
 *		   colons (:) with current working directory.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */
char *fill_path_dir(char *path)
{
	int i, len = 0;
	char *cp_path, *pwd;

	pwd = *(_my_getenv("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				len += _mystrlen(pwd) + 1;
			else
				len++;
		}
		else
			len++;
	}
	cp_path = malloc(sizeof(char) * (len + 1));
	if (!cp_path)
		return (NULL);
	cp_path[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_mystrcat(cp_path, pwd);
				_mystrcat(cp_path, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_mystrcat(cp_path, ":");
				_mystrcat(cp_path, pwd);
			}
			else
				_mystrcat(cp_path, ":");
		}
		else
		{
			_mystrncat(cp_path, &path[i], 1);
		}
	}
	return (cp_path);
}

/**
 * dir_path - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
list_t *dir_path(char *path)
{
	int i;
	char **dirs, *path_cp;
	list_t *head = NULL;

	path_cp = fill_path_dir(path);
	if (!path_cp)
		return (NULL);
	dirs = _mystrtok(path_cp, ":");
	free(path_cp);
	if (!dirs)
		return (NULL);

	for (i = 0; dirs[i]; i++)
	{
		if (end_node_add(&head, dirs[i]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}

