#include "zsh.h"
#include <stdlib.h>

/**
 * zsh_memcpy - copies data from source to destination pointer.
 * @dest: destination pointer.
 * @src:source pointer.
 * @size: size, in bytes to copy.
 *
 * Return: no return value.
 */
void zsh_memcpy(void *dest, const void *src, size_t size)
{
	const char *zsh_src = (const char *)src;
	char *zsh_dest = (char *)dest;

	for (size_t i = 0; i < size; i++)
	{
		zsh_dest[i] = zsh_src[i];
	}
}

/**
 * zsh_realloc - reallocates memory block for a pointer.
 * @ptr: pointer to reallocate.
 * @old_size: size, in bytes, of the allocated memory block.
 * @new_size: size, in bytes, of the new memory block.
 *
 * Return: ptr if new_size == old_size. NULL if malloc fails.
 */
void *zsh_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *nptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
		free(ptr);
		return (NULL);

	if (new_size == old_size)
		return (ptr);

	nptr = malloc(new_size);
	if (nptr == NULL)
		return (NULL);

	if (new_size > old_size)
		zsh_memcpy(nptr, ptr, old_size);
	else
		zsh_memcpy(nptr, ptr, new_size);

	free(ptr);
	return (nptr);
}

/**
 * zsh_reallocdp - reallocates memory block of a double pointer.
 * @ptr: pointer to reallocate.
 * @old_size: size, in bytes, of the allocated memory block.
 * @new_size: size, in bytes, of the new memory block.
 *
 * Return: ptr if new_size == old_size. NULL if malloc fails.
 */
char **zsh_reallocdp(char **ptr, size_t old_size, size_t new_size)
{
	char **nptr;

	if (p == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	nptr = malloc(sizeof(char *) * new_size);
	if (nptr == NULL)
		return (NULL);

	if (new_size < old_size)
		zsh_memcpy(nptr, ptr, sizeof(char *) * new_size);
	else
		zsh_memcpy(nptr, ptr, sizeof(char *) * old_size);

	free(ptr);
	return (nptr);
}

/**
 * zsh_rev_string - reverses a null-terminated string.
 * @str: input string to be reversed.
 * Reurn: no return value.
 *
 * Description: it takes a null-term. str as input and reverses it in place.
 */
void zsh_rev_string(char *str)
{
	int length = strlen(str);

	for (int i = 0; i < length / 2; i++)
		char temp = str[i];

		str[i] = str[length - 1 - i];
		str[length - 1 - i] = temp;
}
