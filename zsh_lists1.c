#include "zsh.h"

/**
 * zsh_add_sep_node - add a separator node to the linked list.
 * @head: pointer to the head of the separator list.
 * @sep: the separator character to add.
 * Return: a pointer to the newly created separator node.
 */
zsh_sep_t *zsh_add_sep_node(zsh_sep_t **head, char sep)
{
	zsh_sep_t *newNode = (zsh_sep_t *)malloc(sizeof(zsh_sep_t));

	if (newNode == NULL)
		return (NULL);

	newNode->separator = sep;
	newNode->next = *head;
	*head = newNode;
	return (newNode);
}

/**
 * zsh_free_sep - frees the memory allocated for the separator list.
 * @head: pointer to the head of the separator list.
 */
void zsh_free_sep(zsh_sep_t **head)
{
	while (*head != NULL)
	{
		zsh_sep_t *temp = *head;
		*head = (*head)->next;
		free(tenmp);
	}
}

/**
 * zsh_add_line_node - adds a command line node to the linked list.
 * @head: pointer to the head of the command line list.
 * @line: the command line string to add.
 * Return: a pointer to the newly created command line node.
 */
zsh_cmdln_t *zsh_add_line_node(zsh_cmdln_t **head, char *line)
{
	zsh_cmdln_t *newNode = (zsh_cmdln_t *)malloc(sizeof(zsh_cmdln_t));

	if (newNode == NULL)
		return (NULL);

	newNode->line = line;
	newNode->next = *head;
	*head = newNode;
	return (newNode);
}

/**
 * * zsh_free_line - frees the memory allocated for the command line list.
 * @head: pointer to the head of the command line list.
 */
void zsh_free_line(zsh_cmdln_t **head)
{
	while (*head != NULL)
	{
		zsh_cmdln_t *temp = *head;
		*head = (*head)->next;
		free(temp->line);
		free(temp);
	}
}
