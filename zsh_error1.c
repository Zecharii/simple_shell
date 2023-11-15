#include "zsh.h"

/**
 * zsh_strcat_cd - function that concatenates the message for cd error.
 * @datash: pointer for the zsh_shell structure.
 * @msg: message to print.
 * @error_msg: the output error message.
 * @v_str: counter lines.
 * Return: the error message.
 */
char *zsh_strcat_cd(zsh_shell *datash, char *msg, char *error_msg, char *v_str)
{
	char *illegal_flag;

	zsh_strcpy(error_msg, datash->av[0]);
	zsh_strcat(error_msg, ": ");
	zsh_strcat(error_msg, v_str);
	zsh_strcat(error_msg, ": ");
	zsh_strcat(error_msg, datash->args[0]);
	zsh_strcat(error_msg, msg);

	if (datash->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = datash->args[1][1];
		illegal_flag[2] = '\0';
		zsh_strcat(error_msg, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		zsh_strcat(error_msg, datash->args[1]);
	}

	zsh_strcat(error_msg, "\n");
	zsh_strcat(error_msg, "\0");

	return (error_msg);
}

/**
 * zsh_getcd_err - gets an error message for cd command.
 * @datash: pointer to the zsh_shell structure.
 * Return: a string containing the error message.
 */
char *zsh_getcd_err(struct zsh_shell *datash)
{
	int len, len_id;
	char *error_msg, *v_str, *msg;

	v_str = zsh_itoa(datash->counter);

	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": Can't cd to ";
		len_id = zsh_strlen(datash->args[1]);
	}

	len = zsh_strlen(datash->av[0]) + zsh_strlen(datash->args[0]);
	len += zsh_strlen(v_str) + zsh_strlen(msg) + len_id + 5;
	error_msg = malloc(sizeof(char) * (len + 1));

	if (error_msg == 0)
	{
		free(v_str);
		return (NULL);
	}

	error_msg = zsh_strcat_cd(datash, msg, error_msg, v_str);

	free(v_str);

	return (error_msg);
}

/**
 * zsh_notfound_err - gets an error message for a command not found.
 * @datash: pointer to the zsh_shell structure.
 * Return: a string containing the error message.
 */
char *zsh_notfound_err(struct zsh_shell *datash)
{
	int len;
	char *error_msg;
	char *v_str;

	v_str = zsh_itoa(datash->counter);
	len = zsh_strlen(datash->av[0]) + zsh_strlen(v_str);
	len += zsh_strlen(datash->args[0]) + 16;
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
	zsh_strcat(error_msg, ": not found\n");
	zsh_strcat(error_msg, "\0");
	free(v_str);
	return (error_msg);
}

/**
 * zsh_exit_err - gets an error message for the exit command.
 * @datash: pointer to the zsh_shell structure.
 * Return: a string containing the error message.
 */
char *zsh_exit_err(ztruct zsh_shell *datash)
{
	int len;
	char *error_msg;
	char *v_str;

	v_str = zsh_itoa(datash->counter);
	len = zsh_strlen(datash->av[0]) + zsh_strlen(v_str);
	len += zsh_strlen(datash->args[0]) + zsh_strlen(datash->args[1]) + 23;
	error_msg = malloc(sizeof(char) * (len + 1));

	if (error_msg == 0)
	{
		free(v_str);
		return (NULL);
	}
	zsh_strcpy(error_msg, datash->av[0]);
	zsh_strcat(error_msg, ": ");
	zsh_strcat(error_msg, v_str);
	zsh_strcat(error_msg, ": ");
	zsh_strcat(error_msg, datash->args[0]);
	zsh_strcat(error_msg, ": Illegal number: ");
	zsh_strcat(error_msg, datash->args[1]);
	zsh_strcat(error_msg, "\n\0");
	free(v_str);

	return (error_msg);
}

/**
 * zsh_get_err - handles and displays an error message based on eval.
 * @datash: pointer to the zsh_shell structure.
 * @eval: error code for determining the error message.
 * Return: the error code provided.
 */
int zsh_get_err(struct zsh_shell *datash, int eval)
{
	char *error_msg = NULL;

	switch (eval)
	{
		case 1:
			error_msg = zsh_getcd_err(datash);
			break;
		case 2:
			error_msg = zsh_notfound_err(datash);
			break;
		case 3:
			error_msg = zsh_exit_err(datash);
			break;
		default:
			error_msg = "Unknown Error";
			break;
	}

	if (error_msg)
	{
		write(STDERR_FILENO, error_msg, zsh_strlen(error_msg));
		free(error_msg);
	}

	datash->status = eval;
	return (eval);
}
