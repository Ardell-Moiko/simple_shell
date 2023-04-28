#include "main.h"

void linked_help_env(void);
void linked_help_setenv(void);
void linked_help_unsetenv(void);
void linked_help_history(void);

/**
 * linked_help_env - Displays information on the byshell builtin command 'env'.
 */
void linked_help_env(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, _mystrlen(msg));
}

/**
 * linked_help_setenv -  byshell builtin command 'setenv'.
 */
void linked_help_setenv(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
}

/**
 * linked_help_unsetenv - Displays information on the byshell builtin command
 * 'unsetenv'.
 */
void linked_help_unsetenv(void)
{
	char *msge = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msge, _mystrlen(msge));
	msge = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msge, _mystrlen(msge));
	msge = "message to stderr.\n";
	write(STDOUT_FILENO, msge, _mystrlen(msge));
}
