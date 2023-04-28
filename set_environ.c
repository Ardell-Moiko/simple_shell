#include "main.h"

char **copy_env(void);
void free_env(void);
char **_my_getenv(const char *var);

/**
 * copy_env - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **copy_env(void)
{
	char **new_environ;
	size_t dimention;
	int index;

	for (dimention = 0; environ[dimention]; dimention++)
		;

	new_environ = malloc(sizeof(char *) * (dimention + 1));
	if (!new_environ)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_environ[index] = malloc(_mystrlen(environ[index]) + 1);

		if (!new_environ[index])
		{
			for (index--; index >= 0; index--)
				free(new_environ[index]);
			free(new_environ);
			return (NULL);
		}
		_mystrcpy(new_environ[index], environ[index]);
	}
	new_environ[index] = NULL;

	return (new_environ);
}

/**
 * free_env - Frees the the environment copy.
 */
void free_env(void)
{
	int lead;

	for (lead = 0; environ[lead]; lead++)
		free(environ[lead]);
	free(environ);
}

/**
 * _my_getenv - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **_my_getenv(const char *var)
{
	int index, len;

	len = _mystrlen(var);
	for (index = 0; environ[index]; index++)
	{
		if (_mystrncmp(var, environ[index], len) == 0)
			return (&environ[index]);
	}

	return (NULL);
}
