#include "zsh.h"

/**
 * zsh_alias_err - generates an error message for alias-related error.
 * @args: array of arguments related to the error.
 * Return: A string containing the error message.
 */
char *zsh_alias_err(const char **args)
{
	int len;
	char *error_msg;

	len = zsh_strlen(args[0]) + zsh_strlen(": Alias error\n");
	error_msg = malloc(sizeof(char) * (len + 1));

	if (error_msg == NULL)
		return (NULL);

	zsh_strcpy(error_msg, arg[0]);
	zsh_strcat(error_msg, ": Alias error\n");

	return (error_msg);
}

/**
 * zsh_env_err - generates an error message for an env-related error.
 * @datash: pointer to the zsh_shell structure.
 * Return: a string containing the error message.
 */
char *zsh_env_err(struct zsh_shell *datash)
{
	int len;
	char *error_msg;
	char *v_str;
	char *msg;

	v_str = zsh_itoa(datash->counter);
	msg = ": Unable to add/remove from environment\n";
	len = zsh_strlen(datash->av[0]) + zsh_strlen(v_str);
	len += zsh_strlen(datash->args[0]) + zsh_strlen(msg) + 4;
	error_msg = malloc(sizeof(char) * (len + 1));

	if (error_msg == 0)
	{
		free(error_msg);
		free(v_str);
		return (NULL);
	}

	zsh_strcpy(error_msg, datash->av[0]);
	zsh_strcat(error_msg, ": ");
	zsh_strcat(error_msg, v_str);
	zsh_strcat(error_msg, ": ");
	zsh_strcat(error_msg, datash->args[0]);
	zsh_strcat(error_msg, msg);
	zshzsh_strcat(error_msg, "\0");
	free(v_str);

	return (error_msg);
}

/**
 * zsh_syntax_err - generates an error message for syntax-related error.
 * @args: arrays of arguments related to the error.
 * Return: a string containing the error message.
 */
char *zsh_syntax_err(const char **args)
{
	int len;
	char *error_msg;

	len = zsh_strlen(args[0]) + zsh_strlen(": Syntax error\n");
	error_msg = malloc(sizeof(char) * (len + 1))

	if (error_msg == NULL)
		return (NULL);

	zsh_strcpy(error_msg, args[0]);
	zsh_strcat(error_msg, ": Syntax error\n");

	return (error_msg);
}

/**
 * zsh_perm_err - generates an error message for a permission-related error.
 * @args: array of arguments related to the error.
 * Return: a string containing the error message.
 */
char *zsh_perm_err(const char **args)
{
	int len;
	char *error_msg;

	len = _strlen(args[0]) + _strlen(": Permission denied\n");
	error_msg = malloc(sizeof(char) * (len + 1));

	if (error_msg == NULL)
		return (NULL);

	zsh_strcpy(error_msg, args[0]);
	zsh_strcat(error_msg, ": Permission denied\n");

	return (error_msg);
}

/**
 * zsh_path126_err - generates an error message for a path-related error.
 * @datash: Pointer to the zsh_shell structure.
 * Return: A string containing the error message.
 */
char *zsh_path126_err(struct zsh_shell *datash)
{
	int len;
	char *v_str;
	char *error_msg;

	v_str = zsh_itoa(datash->counter);
	len = zsh_strlen(datash->av[0]) + zsh_strlen(v_str);
	len += zsh_strlen(datash->args[0]) + 24;
	error_msg = malloc(sizeof(char) * (len + 1));

	if (error_msg == 0)
	{
		free(error_msg);
		free(v_str);
		return (NULL);
	}

	zsh_strcpy(error_msg, datash->av[0]);
	zsh_strcat(error_msg, ": ");
	zsh_strcat(error_msg, v_str);
	zsh_strcat(error_msg, ": ");
	zsh_strcat(error_msg, datash->args[0]);
	zsh_strcat(error_msg, ": Permission denied\n");
	zsh_strcat(error_msg, "\0");
	free(v_str);

	return (error_msg);
}
