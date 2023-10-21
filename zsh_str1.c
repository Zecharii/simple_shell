#include "zsh.h"

/**
 * zsh_strcat - concatenates strings.
 * @dest: destination string.
 * @src: source string to append.
 * Return: a pointer to the beginning of the concatenated string.
 */
char *zsh_strcat(char *dest, const char *src)
{
	char *ptr = dest;

	while (*dest != '\0')
	{
		dest++;
	}
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';

	return (ptr);
}

/**
 * zsh_strcmp - compares strings.
 * @str1: first string for comaprison.
 * @str2: second string for comaparison.
 * Return: an integer <, =, or > zero if str1 is found.
 */
int zsh_strcmp(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}

	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

/**
 * zsh_strchr - searches a string character.
 * @str: string to search.
 * @c: character to search for.
 * Return: a ptr to the first occurrence of the chr in str. Else, NULL.
 */
char *zsh_strchr(const char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}

	return (NULL);
}

/**
 * zsh_strspn - search string span.
 * @str: string to search withtin.
 * @accept: the characters to search for.
 * Return: length of the intial segment of str that consists of chrs found.
 */
int zsh_strspn(const char *str, const char *accept)
{
	int count = 0;

	while (*str && zsh_strchr(accept, *str))
	{
		count++;
		str++;
	}

	return (count);
}
