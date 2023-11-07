#include "main.h"

/**
 * zsh_repeat_char - checks if a character repeats 'z' times in a row.
 * @input: the input string to check.
 * @z: number of repetitions to check for.
 * Return: 1 if the character repeats 'z' times in a row, otherwise 0.
 */
int zsh_repeat_char(const char *input, int z)
{
	int count = 1;

	for (int i = 1; input[i] != '\0'; i++)
	{
		if (input[i] == input[i - 1])
		{
			count++;
			if (count == z)
			{
				return (1);
			}
		}
		else
		{
			count = 1;
		}
	}
	return (0);
}

/**
 * zsh_sep_op - checks if the character 'last' is a separator operator.
 * @input: the input string to check.
 * @z: value for determining the character repetition.
 * @last: the last character in the input.
 * Return: 1 if 'last' is a separator operator, otherwise 0.
 */
int zsh_sep_op(const char *input, int z, char last)
{
	if ((last == ';' || last == '|') && z > 1)
		return (1);
	return (0);
}

/**
 * zsh_first_char - sets 'z' according to the first character in the input.
 * @input: the input string to anlayze.
 * @z: pointer to the integer to be set.
 * Return: 1 for a successful check.
 */
int zsh_first_char(const char *input, int *z)
{
	if (input[0] == '$')
		*z = 2;
	else
		*z = 1;
	return (1);
}

/**
 * zsh_print_error - prints an error or warning message based on a bool flag.
 * @datash: pointer to the zsh_shell structure.
 * @input: the input causing the error or warning.
 * @z: value for determining the character repetition.
 * @b: boolean flag (1 for error, 0 for warning).
 */
void zsh_print_error(struct zsh_shell *datash, const char *input, int z, int b)
{
	if (b)
		printf("Error: %s\n", input);
	else
		printf("Warning: %s\n", input);
}

/**
 * zsh_check_error - checks for errors in the input and prints messages.
 * @datash: pointer to the zsh_shell structure.
 * @input: the input string to check for errors.
 * Return: 1 if an error is found, otherwise 0.
 */
int zsh_check_error(struct zsh_shell *datash, const char *input)
{
	int z = 1;

	if (!zsh_first_char(input, &z))
		zsh_print_error(datash, "Invalid first character.", z, 1);
		return (1);

	if (zsh_repeat_char(input, z))
		zsh_print_error(datash, "Character repeated too many times.", z, 1);
		return (1);

	if (zsh_sep_op(input, z, input[strlen(input) - 1]))
		zsh_print_error(datash, "Least character is a separator operator.", z, 1);
		return (1);

	return (0);
}
