#include "zsh.h"

/**
 * zsh_get_len - calculates the length of a number.
 * @n: type int number.
 * Return: length of a number.
 */
int zsh_get_len(int n)
{
	int count = 0;

	if (n < 0)
		count++;
		n = -n;

	while (n != 0)
	{
		n /= 10;
		count++;
	}

	return (count);
}

/**
 * zsh_itoa - converts an integer to a string.
 * @n: the integer to convert to astring.
 * Return: a string representation of the integer.
 */
char *zsh_itoa(int n)
{
	int len = zsh_get_len(n);
	char *buffer = (char *)malloc((len + 1) * sizeof(char));

	if (buffer == NULL)
		return (NULL);

	if (n < 0)
		buffer[0] = '-';
		n = -n;

	int index = len - 1;

	while (n != 0)
	{
		buffer[index--] = (n % 10) + '0';
		n /= 10;
	}

	buffer[len] = '\0';

	return (buffer);
}

/**
 * zsh_atoi - converts a string to an integer.
 * @s: the string to convert to an integers.
 * Return: the converted integer value.
 */
int zsh_atoi(const char *s)
{
	int result = 0, sign = 1, i = 0;

	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
	{
		i++;
	}

	if (s[i] == '-')
		sign = -1;
		i++;
	else if (s[i] == '+')
		i++;

	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i] - '0');
		i++;
	}

	return (sign * result);
}

/**
 * zsh_get_sigint - signal handler function for SIGINT.
 * @sig: the signal handler.
 */

void zsh_get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
