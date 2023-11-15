#include "zsh.h"

/**
 * zsh_help - help information for the builtin env.
 * Return: no return value.
 */
void zsh_help(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, zsh_strlen(help));
	help = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, help, zsh_strlen(help));
}

/**
 * zsh_help_alias - Help information for the builtin alias.
 * Return: no return value.
 */
void zsh_help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, zsh_strlen(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, zsh_strlen(help));
}

/**
 * zsh_help_cd - help information for the builtin alias.
 * Return: no return value.
 */
void zsh_help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, zsh_strlen(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, zsh_strlen(help));
}

/**
 * zsh_get_help - retrieves help for a specific command.
 * @datash: pointer to the zsh_shell structure.
 * Return: 0 on successful retrieval, -1 otherwise.
 */
int zsh_get_help(struct zsh_shell *datash)
{

	if (datash->args[1] == 0)
		zsh_help_general();
	else if (zsh_strcmp(datash->args[1], "setenv") == 0)
		zsh_help_setenv();
	else if (zsh_strcmp(datash->args[1], "env") == 0)
		zsh_help_env();
	else if (zsh_strcmp(datash->args[1], "unsetenv") == 0)
		zsh_help_unsetenv();
	else if (zsh_strcmp(datash->args[1], "help") == 0)
		zsh_help();
	else if (zsh_strcmp(datash->args[1], "exit") == 0)
		zsh_help_exit();
	else if (zsh_strcmp(datash->args[1], "cd") == 0)
		zsh_help_cd();
	else if (zsh_strcmp(datash->args[1], "alias") == 0)
		zsh_help_alias();
	else
		write(STDERR_FILENO, datash->args[0],
		      zsh_strlen(datash->args[0]));

	datash->status = 0;
	return (1);
}
