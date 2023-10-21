#include "zsh.h"

/**
 * zsh_strdup - duplicates a string.
 * @str: string to be duplicated.
 * Return: a pointer to a newly allocated str, which is a dup of str.
 */
char *zsh_strdup(const char *str)
{
	int length = zsh_strlen(str);
	char *duplicate = (char *)malloc(length + 1);

	if (duplicate == NULL)
		return (NULL);

	zsh_strcpy(duplicate, str);

	return (duplicate);
}

/**
 * zsh_strlen - calculates the length of a string.
 * @str: string to be measured.
 * Return: the number of chars in the str, excluding null-terminator.
 */
int zsh_strlen(const char *str)
{
	int length = 0;

	while (*str)
	{
		length++;
		str++;
	}
	return (length);
}

/**
 * zsh_charcmp - compares a chr in a str wih a set of delim.
 * @str: string to search within.
 * @delim: set of delimiter characters.
 * Return: 1 if the chr at current position in str is found in delim. Else, 0.
 */
int zsh_charcmp(char str[], const char *delim)
{
	return (zsh_strchr(delim, str[0] != NULL));
}

/**
 * zsh_strtok - tokenize a string using a set of delims.
 * @str: string to be tokenized.
 * @delim: set of delimiter characters.
 * Return: a pointer to next token in str. Else, NULL if no more tokens.
 */
char *zsh_strtok(char str[], const char *delim)
{
	char *lastToken = NULL;

	if (str != NULL)
		lastToken = str;
	else
		if (lastToken == NULL)
			return (NULL);
	while (zsh_charcmp(lastToken, delim))
	{
		lastToken++;
	}

	if (*lastToken == '\0')
		return (NULL);

	char *tokenStart = lastToken;

	while (*lastToken != '\0' && !zsh_charcmp(lastToken, delim))
	{
		lastToken++;
	}

	if (*lastToken != '\0')
		*lastTokeen = '\0';
		lastToken++;

	return (tokenStart);
}

/**
 * zsh_isdigit - checks if a str represents a numeric value.
 * @str: string to be checked.
 * Return: 1 if the str ia valid numeric value. Else, 0.
 */
int zsh_isdigit(const char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);

		str++;
	}
	return (1);
}


