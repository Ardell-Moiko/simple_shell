#include "main.h"

void linked_help_all(void);
void linked_help_alias(void);
void linked_help_cd(void);
void linked_help_exit(void);
void linked_help_help(void);

/**
 * linked_help_all - Displays all possible builtin byshell commands.
 */
void linked_help_all(void)
{
	char *msg = "Shellby\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = "out more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
}

/**
 * linked_help_alias -  builtin command 'alias'.
 */
void linked_help_alias(void)
{
	char *msg = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
}

/**
 * linked_help_cd -  builtin command 'cd'.
 */
void linked_help_cd(void)
{
	char *msg = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = "after a change of directory.\n";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
}

/**
 * linked_help_exit -  command 'exit'.
 */
void linked_help_exit(void)
{
	char *msg = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = " exit 0.\n";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
}

/**
 * linked_help_help - builtin command 'help'.
 */
void linked_help_help(void)
{
	char *msg = "help: help\n\tSee all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
	msg = "builtin command.\n";
	write(STDOUT_FILENO, msg, _mystrlen(msg));
}
