#include "zsh.h"

/**
 * zsh_getenv - gets the value of an environment variable.
 * @name: the name of the environment variable to retrieve.
 * @zsh_envvars: pointer to the array of environment variables.
 * Return: a pointer to the value of the specified environment variable.
 */
char *zsh_getenv(const char *name, char **zsh_envvars)
{
	if (zsh_envvars == NULL)
		return (NULL);

	for (int i = 0; zsh_envvars[i] != NULL; i++)
	{
		char *envvar = zsh_envvars[i];

		if (zsh_strncmp(envvar, name, zsh_strlen(name)) == 0 &&
				(envvar[zsh_strlen(name)] == '=')
			return (&envvar[zsh_strlen(name) + 1]);
	}

	return (NULL);
}

/**
 * zsh_env - prints the environment variables.
 * @datash: data relevant to the zsh_shell structure.
 * Return: 1 on success.
 */
int zsh_env(struct zsh_shell *datash)
{
	int i, j;

	for (i = 0; datash->zsh_envvars[i]; i++)
	{
		for (j = 0; datash->zsh_envvars[i][j]; j++)
			;

		write(STDOUT_FILENO, datash->zsh_envvars[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}

/**
 * zsh_set_env - sets an environment variable.
 * @name: the name of the environment variable to set.
 * @value: the value to assign to the environment variable.
 * @datash: pointer to the zsh_shell structure.
 */
void zsh_set_env(const char *name, const char *value, struct zsh_shell *datash)
{
	char **envvars = datash->zsh_envvars;

	if (envvars == NULL)
		return;

	for (int i = 0; envvars[i] != NULL; i++)
	{
		if (zsh_strncmp(envvars[i], name, zsh_strlen(name)) == 0 &&
				envvars[i][zsh_strlen(name)] == '=')
			char *new_var = (char *)malloc(zsh_strlen(name) + zsh_strlen(value) + 2);

			snprintf(new_var, zsh_strlen(name) + zsh_strlen(value) +
					2, "%s=%s", name, value);
			free(envvars[i]);
			envvars[i] = new_var;
			return;
	}

	int count = 0;

	while (envvars[count] != NULL)
		count++

	char *new_var = (char *)malloc(zsh_strlen(name) + zsh_strlen(value) + 2);

	snprintf(new_var, zsh_strlen(name) + zsh_strlen(value) +
			2, "%s=%s", name, value);
	envvars[count] = new_var;
	envvars[count + 1] = NULL;
}

/**
 * zsh_setenv - compares environment variable names with the nae passed.
 * @datash: pointer to the zsh_shell structure.
 * Return: 1 on success.
 */
int zsh_setenv(struct zsh_shell *datash)
{
	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		zsh_get_err(datash, -1);
		return (1);
	}

	zsh_set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * zsh_unsetenv - unsets an environment variable.
 * @name: the name of the environment variable to unset.
 * @datash: pointer to the zsh_shell structure.
 * Return: 1 on success.
 */
int zsh_unsetenv(const char *name, struct zsh_shell *datash)
{
	char **envvars = datash->zsh_envvars;

	if (envvars == NULL)
		return (-1);

	for (int i = 0; envvars[i] != NULL; i++)
	{
		if (zsh_strncmp(envvars[i], name, zsh_strlen(name)) == 0 &&
				envvars[i][zsh_strlen(name)] == '=')
		{
			free(envvars[i]);

			for (int j = i; envvars[j] != NULL; j++)
			{
				envvars[j] = envvars[j + 1];
			}
			return (0);
		}
	}

	return (-1);
}
