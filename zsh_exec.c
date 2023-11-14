#include "zsh.h"

/**
 * zsh_is_cdir - checks if ":" is in the current directory.
 * @path: type char pointer.
 * @z: type int pointer of index.
 * Return: 1 if path is searchable in cd, otherwise 0.
 */
int zsh_is_cdir(const char *path, int *z)
{
	if (path[*z] == ':')
		return (1);

	while (path[*z] != ':' && path[*z])
		*z += 1;

	if (path[*z])
		*z += 1;

	return (0);
}

/**
 * zsh_which - locates the executable path of a command.
 * @cmd: the command for which to find the executable path.
 * @zsh_envvars: environment variables.
 * Return: a string containing the path to the executable command or NULL.
 */
char *zsh_which(const char *cmd, char **zsh_envvars)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, z;
	struct stat st;

	path = zsh_getenv("PATH", zsh_envvars);

	if (path)
		ptr_path = zsh_strdup(path);
		len_cmd = zsh_strlen(cmd);
		token_path = zsh_strtok(ptr_path, ":");
		z = 0;

		while (token_path != NULL)
			if (zsh_is_cdir(path, &z))
				if (stat(cmd, &st) == 0)
					return (zsh_strdup(cmd));

			len_dir = zsh_strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			zsh_strcpy(dir, token_path);
			zsh_strcat(dir, "/");
			zsh_strcat(dir, cmd);
			zsh_strcat(dir, "\0");

			if (stat(dir, &st) == 0)
				free(ptr_path);
				return (dir);

			free(dir);
			token_path = zsh_strtok(NULL, ":");

		free(ptr_path);

		if (stat(cmd, &st) == 0)
			return (zsh_strdup(cmd));

		return (NULL);

	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (zsh_strdup(cmd));

	return (NULL);
}

/**
 * zsh_is_exec - checks if a command is an executable.
 * @datash: pointer to the zsh_shell structure.
 * Return: 1 if the command is executable, 0 otherwise.
 */
int zsh_is_exec(struct zsh_shell *datash)
{
	struct stat y;
	int i;
	char *input;

	input = datash->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &y) == 0)
	{
		return (i);
	}
	zsh_get_error(datash, 127);
	return (-1);
}

/**
 * zsh_error_cmd - checks if a user has permissions to access a command.
 * @dir: The directory where the command cannot be executed.
 * @datash: Pointer to the zsh_shell structure.
 * Return: -1 for command execution failure.
 */
int zsh_error_cmd(const char *dir, struct zsh_shell *datash)
{
	if (dir == NULL)
	{
		zsh_get_err(datash, 127);
		return (1);
	}

	if (zsh_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			zsh_get_err(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			zsh_get_err(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * zsh_cmd_exec - Executes a command line in the shell.
 * @datash: Pointer to the zsh_shell structure.
 * Return: 1 on successful execution.
 */
int zsh_cmd_exec(struct zsh_shell *datash)
{
	pid_t pd, wpd;
	int state, exec;
	char *dir;
	(void) wpd;

	exec = zsh_is_exec(datash);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = zsh_which(datash->args[0], datash->_environ);
		if (zsh_check_error(dir, datash) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = zsh_which(datash->args[0], datash->_environ);
		else
			dir = datash->args[0];
		execve(dir + exec, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datash->status = state / 256;
	return (1);
}
