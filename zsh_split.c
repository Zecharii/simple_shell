#include "main.h"

/**
 * zsh_swap_char - swaps characters in a string based on a boolean condition.
 * @input: the input string.
 * @bool: boolean condition (1 for swapping, 0 for no swap).
 * Return: a pointer to the modified string.
 */
char *zsh_swap_char(char *input, int bool)
{
	if (bool)
		char temp = input[0];

		input[0] = input[1];
		input[1] = temp;

	return (input);
}

/**
 * zsh_add_nodes - adds separator and command line nodes to linked lists.
 * @head_s: pointer to the head of the separator list.
 * @head_l: pointer to the head of the command line list.
 * @input: the input string.
 */
void zsh_add_nodes(zsh_sep_t **head_s, zsh_xmdln_t **head_l, char *input)
{
	if (input == NULL || input[0] == '\0')
		return;

	zsh_sep_t *sepNode = (zsh_sep_t *)malloc(sizeof(zsh_sep_t));

	if (sepNode == NULL)
		return;

	sepNode->separator = input[0];
	sepNode->next = *head_s;
	*head_s = sepNode;

	input++;

	char *line = zsh_strdup(input);
	zsh_cmdln_t *lineNode = (zsh_cmdln_t *)malloc(sizeof(zsh_cmdln_t));

	if (lineNode == NULL)
		free(line);
		return;

	lineNode->line = line;
	lineNode->next = *head_l;
	*head_l = lineNode;
}

/**
 * zsh_go_next - moves to the next separator and command line in the lists.
 * @list_s: pointer to the separator list.
 * @list_l: separator to the command line list.
 * @datash: pointer to zsh_shell structure for data storage.
 */
void zsh_go_next(zsh_sep_t **list_s, zsh_cmdln_t **list_l, zsh_shell *datash)
{
	if (*list_s != NULL)
		zsh_sep_t *temp_s = *list_s;
		*list_s = (*list_s)->next;
		free(temp_s);

	if (*list_l != NULL)
		zsh_cmdln_t *temp_l = *list_l;
		*list_l = (*list_l)->next
		free(temp_l->line);
		free(temp_l);

	datash->current_separator = (*list_s != NULL) ? (*list_s)->separator : '\0';
}

/**
 * zsh_split_command - splits a command into separator-separated parts.
 * @datash: pointer to zsh_shell structure for data storage.
 * @input: the input command string.
 * Return: the number of parts into whick the command is split.
 */
int zsh_split_command(zsh_shell *datash, char *input)
{
	zsh_sep_t *separators = NULL;
	zsh_cmdln_t *commandLines = NULL;
	int parts = 0;

	while (*input)
	{
		zsh_add_nodes(&separators, &commandLines, input);
		zsh_go_next(&separators, &commandLines, datash);
		parts++;
	}

	datash->separators = separators;
	datash->command_lines = commandLines;
	datash->current_separator = separators ? separators->separator : '\0';

	return (parts);
}

/**
 * zsh_split_line - splits a line into individual parts.
 * @input: the input line string.
 * Return: an array of strings representing the parts of the line.
 */
char **zsh_split_line(char *input)
{
	char **parts = NULL;
	int num_parts = 0;

	char *token = strtok(input, " ");

	while (token != NULL)
	{
		num_parts++;
		parts = (char **)realloc(parts, num_parts * sizeof(char *));

		if (parts == NULL)
			for (int i = 0; i < num_parts - 1; i++)
			{
				free(parts[1]);
			}
			free(parts);
			return (NULL);

		part[num_parts - 1] = zsh_strdup(token);
		token = strtok(NULL, " ");
	}

	num_part++;
	parts = (char **)realloc(parts, num_parts * sizeof(char *));

	if (parts == NULL)
		for (int i = 0; i < num_parts - 1; i++)
		{
			free(parts[i]);
		}
		return (NULL);

	parts[num_parts - 1] = NULL;

	return (parts);
}

