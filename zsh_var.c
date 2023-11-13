#include "zsh.h"

/**
 * zsh_check_env - checks if the type variable is an environment variable.
 * @head: pointer to the head of the variable list.
 * @z: the name of the environment variable to check.
 * @datash: pointer to the zsh_shell structure.
 */
void zsh_check_env(struct zsh_var_t **head, char *z, struct zsh_shell *datash)
{
	int row, chr, j, lval;
	char **envr;

	envr = datash->zsh_envvars;

	for (row = 0; envr[row]; row++)
	{
		for (j = 1; chr = 0; envr[row][chr]; chr++)
		{
			if (envr[row][chr] == '=')
			{
				lval = zsh_strlen(envr[row] + chr + 1);
				zsh_add_rvar_node(head, j, envr[row] + chr + 1, lval);
				return;
			}

			if (z[j] == envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; z[j]; j++)
	{
		if (z[j] == ' ' || z[j] == '\t' || z[j] == ';' || z[j] == '\n')
			break;
	}

	zsh_add_rvar_node(head, j, NULL, 0);
}

/**
 * zsh_check_vars - checks if the typed variable is $$ or $.
 * @head: pointer to the head of the variable list.
 * @z: the name of the variable to check.
 * @y: the string to store the value of the variable.
 * @datash: pointer to the zsh_shell structure.
 * Return: no return value.
 */
int zsh_check_vars(zsh_var_t **head, char *z, char *y, zsh_shell *datash)
{
	int i, lst, lpd;

	lst = zsh_strlen(y);
	lpd = zsh_strlen(datash->pid);

	for (i = 0; z[i]; i++)
	{
		if (z[i] == '$')
			if (z[i + 1] == '?')
				zsh_add_rvar_node(head, 2, y, lst), i++;
			else if (z[i + 1] == '$')
				zsh_add_rvar_node(head, 2, datash->pid, lpd), i++;
			else if (z[i + 1] == '\n')
				zsh_add_rvar_node(head, 0, NULL, 0);
			else if (z[i + 1] == '\0')
				zsh_add_rvar_node(head, 0, NULL, 0);
			else if (z[i + 1] == ' ')
				zsh_add_rvar_node(head, 0, NULL, 0);
			else if (z[i + 1] == '\t')
				zsh_add_rvar_node(head, 0, NULL, 0);
			else if (z[i + 1] == ';')
				zsh_add_rvar_node(head, 0, NULL, 0);
			else
				zsh_check_env(head, z + 1, datash);
	}

	return (i);
}

/**
 * zsh_rep_input - replaces variables in the input string with their value.
 * @head: pointer to the hea of the variable list.
 * @input: the input string to process.
 * @new_input: the string to store the processed input.
 * @nlen: length of the new_input string.
 * Return: a pointer with replaced variables or NULL.
 */
char *zsh_rep_input(zsh_var_t **head, char *input, char *new_input, int nlen)
{
	char *result = (char *)malloc(nlen);

	if (result == NULL)
		return (NULL);

	int input_len = zsh_strlen(input), result_index = 0;

	for (int i = 0; i < input_len; i++)
		if (input[i] == '$' && i + 1 < input_len)
			int j = i + 1;

			while (j < input_len && input[j] != ' ' && input[j] != '$')
				j++;

			char var_name[j - 1];

			zsh_strcpy(var_name, &input[i + 1], j - i - 1);
			var_name[j - i - 1] = '\0';

			struct zsh_var_t *current = *head;

			while (current != NULL)
				if (zsh_strcmp(current->name, var_name) == 0)
					zsh_strcat(result, current->value);
					result_index += zsh_strlen(current->value);
					break;
				current = current->next;

			i = j - 1;
		else
			result[result_index++] = input[i];

	result[result_index] = '\0';

	if (new_input != NULL)
		zsh_strcpy(new_input, result);

	return (result);
}

/**
 * zsh_rep_var - replaces variables in a string with their values in the shell.
 * @input: the input string containing variables to replace.
 * @datash: pointer to the zsh_shell structure.
 * Return: a pointer to a new string with replaced variables or NULL.
 */
char *zsh_rep_var(char *input, struct zsh_shell *datash)
{
	size_t input_len = zsh_strlen(input);
	char *new_input = (char *)malloc(input_len + 1);

	if (new_input == NULL)
	{
		return (NULL);
	}

	new_input = zsh_rep_input(&datash->variables, input, new_input, input_len);
	return (new_input);
}
