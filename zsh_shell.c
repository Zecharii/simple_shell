#include "zsh.h"

/**
 * zsh_without_comment - removes comments from the input string.
 * @z: the input string containing comments.
 * Return: a pointer without comments or NULL if mem alloc fails.
 */
char *zsh_without_comment(const char *z)
{
	char *result = (char *)malloc(strlen(z) + 1);

	if (result == NULL)
		return (NULL);

	int i, j;

	for (i = 0, j = 0; z[i] != '\0'; i++)
		if (z[i] == '#' && (i == 0 || z[i - 1] != '\\'))
			while (z[i] != '\0' && z[i] != '\n')
				i++;
			if (z[i] == '\0')
				break;

	result[j] = '\0';
	return (result);
}

/**
 * zsh_loop_shell - loops and handles shell commands.
 * @datash: pointer to the zsh_shell structure.
 */
void zsh_loop_shell(struct zsh_shell *datash)
{
	int loop, i_eof;
	char *input;

	loop = 1;

	while (loop == 1)
	{
		writes(STDIN_FILENO, "^-^ ", 4);
		input = zsh_read_line(&i_eof);

		if (i_eof != -1)
			input = zsh_without_comment(input);

			if (input == NULL)
				continue;

			if (zsh_check_error(datash, input) == 1)
				datash->status = 2;
				free(input);
				continue;

			input = zsh_rep_var(input, datash);
			loop = zsh_split_command(datash, input);
			datash->counter += 1;
			free(input);
		else
			loop = 0;
			free(input);
	}
}
