#include "main.h"
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


/**
 * myunsetenv - Remove an environment variable
 *
 * @state: the state of the shell
 *
 *  Return: 0 in success 1 otherwise
 */
int myunsetenv(state_t *state)
{
	int i;

	if (!state->argv[1])
	{
		write(2, "Too few arguements.\n", 20);

		state->status = 1;
		return (1);
	}
	for (i = 1; state->argv[i]; i++)
	{
		state->status = _unsetenv(state, state->argv[i]) == 0 ? state->status : 1;
	}
	return (0);
}
