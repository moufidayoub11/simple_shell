#include "main.h"

/**
 * _getenv - gets the value of an environ variable
 *
 * @state: the state of the programm
 * @name: the name of the env var
 *
 * Return: the value
 */
char *_getenv(state_t *state, const char *name)
{
	list_t *node = state->env_list;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (++p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _unsetenv - Remove an environment variable
 *
 * @state: the state of the programm
 *  Return: 1 on delete, 0 otherwise
 * @name: the string env name property
 */
int _unsetenv(state_t *state, char *name)
{
	list_t *node = state->env_list;
	size_t i = 0;
	char *p;

	state->environ_changed = 0;

	if (!node || !name)
		return (0);

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p == '=')
		{
			state->environ_changed = delete_node_at_index(&(state->env_list), i);
			i = 0;
			node = state->env_list;
			continue;
		}
		node = node->next;
		i++;
	}
	return (state->environ_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 *
 * @state: the state of the programm
 * @name: the string env name property
 * @value: the string env name value
 *
 *  Return: Always 0
 */
int _setenv(state_t *state, char *name, char *value)
{
	char *temp = NULL;
	list_t *node;
	char *p;

	if (!name || !value)
		return (0);
	temp = malloc(_strlen(name) + _strlen(value) + 2);
	if (!temp)
		return (1);

	strcpy(temp, name);
	_strcat(temp, "=");
	_strcat(temp, value);

	node = state->env_list;
	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = temp;
			state->environ_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(state->env_list), temp, 0);
	free(temp);
	state->environ_changed = 1;
	return (0);
}

/**
 * get_environ - returns the string array copy of our environ
 *
 *  @state: the state of the programm
 *
 *  Return: Always 0
 */
char **get_environ(state_t *state)
{
	if (!state->environ || state->environ_changed)
	{
		state->environ = list_to_strings(state->env_list);
		state->environ_changed = 0;
	}

	return (state->environ);
}


/**
 * init_env_list - populates env linked list
 *
 *  @state: the state of the programm
 *
 *  Return: Always 0
 */
int init_env_list(state_t *state)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], i);
	state->env_list = node;
	return (0);
}
