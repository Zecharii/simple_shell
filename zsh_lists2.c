#include "main.h"

/**
 * zsh_add_rvar_node - add a variable node to the linked list.
 * @head: pointer to the head of the variable list.
 * @lvar: length of the variable name.
 * @var: variable name to add.
 * @lval: length of the variable value.
 * Return: a pointer to the newly created variable node.
 */
zsh_var_t *zsh_add_rvar_node(zsh_var_t **head, int lvar, char *var, int lval)
{
	zsh_var_t *newNode = (zsh_var_t *)malloc(sizeof(zsh_var_t));

	if (newNode == NULL)
		return (NULL);

	newNode->lvar = lvar;
	newNode->var = var;
	newNode->lval = lval;
	newNode->next = *head;
	*head = newNode;
	return (newNode);
}

/**
 * zsh_free_rvar - frees the memory allocated for the variable list.
 * @head: pointer to the head of the variable list.
 */
void zsh_free_rvar(zsh_var_t **head)
{
	while (*head != NULL)
	{
		zsh_var_t *temp = *head;
		*head = (*head)->next;
		free(temp->var);
		free(temp);
	}
}
