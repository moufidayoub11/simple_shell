#include "main.h"


/**
 * add_node_end - Function that adds a new node at the end of a ll
 *
 * @head: the head of a ll
 * @str: the value of the node
 * @index: the index of the node
 *
 * Return: the number of nodes
 */

list_t *add_node_end(list_t **head, char *str, int index)
{
	list_t *temp;
	list_t *new;

	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);

	new->str = _strdup(str);
	if (!new->str)
	{
		free(new);
		return (NULL);
	}

	new->next = NULL;

	if (!(*head))
	{
		(*head) = new;

		return (new);
	}

	temp = (*head);
	while (temp->next)
		temp = temp->next;

	temp->next = new;
	return (new);
}


/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 *
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);

	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = _strdup(node->str);

		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * free_list - Function that frees a linked list
 *
 * @head: the head of a ll
 *
 * Return: void, returns nothing
 */
void free_list(list_t *head)
{
	list_t *temp;

	if (!head)
		return;

	while (head)
	{
		temp = head->next;
		free(head->str);
		free(head);
		head = temp;
	}
}


/**
 * print_list - Function that prints a linked list
 *
 * @h: the linked list
 *
 * Return: the number of nodes
 */

size_t print_list(const list_t *h)
{
	char *value;
	size_t numberOfNodes = 0;

	if (!h)
		return (0);

	while (h)
	{
		value = h->str ? h->str : "(nil)";

		printf("%s\n", value);

		h = h->next;
		numberOfNodes++;
	}

	return (numberOfNodes);
}

/**
 * list_len - Function that counts nodes i ll
 *
 * @h: the linked list
 *
 * Return: the number of nodes
 */

size_t list_len(const list_t *h)
{
	size_t numberOfNodes = 0;

	if (!h)
		return (0);

	while (h)
	{
		h = h->next;
		numberOfNodes++;
	}

	return (numberOfNodes);
}
