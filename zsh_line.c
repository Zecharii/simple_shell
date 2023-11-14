#include "zsh.h"

/**
 * zsh_bring_line - assigns the line variable for the 'get_line' function.
 * @lineptr: pointer to the buffer that stores the input string.
 * @s: size of the lineptr buffer.
 * @buffer: string that is assigned to lineptr.
 * @t: size of the buffer.
 * Return: void.
 */
void zsh_bring_line(char **lineptr, size_t s, char *buffer, size_t t)
{
	if (*lineptr == NULL)
	{
		if (t > BUFFSIZE)
			*s = t;
		else
			*s = BUFFSIZE;
		*lineptr = buffer;
	}
	else if (*s < t)
	{
		if (t > BUFFSIZE)
			*s =  t;
		else
			*s = BUFFSIZE;
		*lineptr = buffer;
	}
	else
	{
		zsh_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * zsh_get_line - reads input from a stream.
 * @lineptr: pointer to the buffer that stores the input.
 * @s: pointer to the size of lineptr.
 * @stream: stream to read from.
 * Return: the number of byter read from the input.
 */
ssize_t zsh_get_line(char **lineptr, size_t *s, FILE *stream)
{
	int x;
	static ssize_t str;
	ssize_t byt;
	char *buf;
	char nchar = 'z';

	if (str == 0)
		fflush(stream);
	else
		return (-1);
	str = 0;
	buf = malloc(sizeof(char) * BUFFSIZE);
	if (buf == 0)
		return (-1);
	while (nchar != '\n')
	{
		x = read(STDIN_FILENO, &nchar, 1);
		if (x == -1 || (x == 0 && str == 0))
		{
			free(buf);
			return (-1);
		}
		if (x == 0 && str != 0)
		{
			str++;
			break;
		}
		if (str >= BUFFSIZE)
			buf = realloc(buf, str, str + 1);
		buf[str] = nchar;
		str++;
	}
	buf[str] = '\0';
	zsh_bring_line(lineptr, s, buf, str);
	byt = str;
	if (x != 0)
		str = 0;
	return (byt);
}

 /**
 * zsh_read_line - reads a line of input.
 * @i_eof: pointer to a flag indicating end of file status.
 * Return: a pointer to the read line.
 */
char *zsh_read_line(int *i_eof)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	*i_eof = 0;

	nread = getline(&line, &len, stdin);

	if (nread == -1)
		*i_eof = 1;

	return (line);
}

/**
 * zsh_exec_line - finds builtins and commands.
 * @datash: pointer to the zsh_shell structure.
 * Return: 1 on success.
 */
int zsh_exec_line(struct zsh_shell *datash)
{
	int (*builtin)(zsh_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = zsh_get_builtin(datash->args[0]);

	if (builtin !=  NULL)
		return (builtin(datash));

	return (zsh_cmd_exec(datash));
}

/**
 * zsh_copy_info - copies info as a stirng.
 * @name: name string.
 * @value: value string.
 * Return: new env or alias.
 */
char *zsh_copy_info(const char *name, const char *value)
{
	char *new;
	int name_str, value_str, len;

	name_str = zsh_strlen(name);
	value_str = zsh_strlen(value);
	len = name_str + valu_stre + 2;
	new = malloc(sizeof(char) * (len));
	zsh_strcpy(new, name);
	zsh_strcat(new, "=");
	zsh_strcat(new, value);
	zsh_strcat(new, "\0");

	return (new);
}
