#include "zsh.h"

/**
 * zsh_init_data - initializes the data struct and populates it.
 * @datash: pointer to the data structure.
 * @argv: argument vector (an array of strings).
 * Return: void.
 */
void zsh_init_data(zsh_shell *datash, char **argv)
{
	unsigned int z;

	datash->zsh_argv = argv;
	datash->zsh_input = NULL;
	datash->zsh_args = NULL;
	datash->zsh_status = 0;
	datash->zsh_counter = 1;

	for (z = 0 ; environ[z] ; z++)
		;
	datash->zsh_envvars = malloc(sizeof(char *) * (z + 1));
	for (z = 0 ; environ[z] ; z++)
	{
		datash->zsh_envvars[x] = zsh_strdup(environ[z]);
	}
	datash->zsh_envvars[z] = NULL;
	datash->pid = _sprintf(getpid());
}

/**
 * zsh_free_data - frees the data structure and associated resources.
 * @datash: pointer to the data structure.
 * Return: void.
 */
void zsh_free_data(zsh_shell *datash)
{
	unsigned int z;

	for (z = 0; datash->zsh_envvars[z] ; z++)
	{
		free(datash->zsh_envvars[z]);
	}
	free(datash->zsh_envvars);
	free(datash->pid);
}

/**
 * main- entry point of the program.
 * @argc: argument count (number of command-line arguments).
 * @argv: argument vector (array of command-line argument strings).
 * Return: 0 on code success.
 */
int main(int argc, char **argv)
{
	zsh_shell datash;
	(void) argc;

	signal(SIGINT, zsh_get_sigint);
	zsh_init_data(&datash, argv);
	zsh_loop_shell(&datash);
	zsh_free_data(&datash);

	if (datash.zsh_status < 0)
		return (255);
	return (datash.zsh_status);
}
