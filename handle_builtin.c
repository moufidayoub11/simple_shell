#include "main.h"

/**
 * myexit - exits the program
 *
 * @state: the state of the shell
 *
 *  Return: -2 if succesful, 1 error
 */
int myexit(state_t *state)
{
	int exitnum;

	if (state->argv[1])
	{
		exitnum = _atoi(state->argv[1]);
		if (exitnum == -1)
		{
			state->status = 2;
			print_error(state, "Illegal number: ");
			write(2, state->argv[1], _strlen(state->argv[1]));
			write(2, "\n", 1);
			return (1);
		}
		state->exit_number = exitnum;
		return (-2);
	}
	state->exit_number = -1;
	return (-2);
}

/**
 * myenv - prints the current environment
 *
 * @state: the state of the shell
 *
 * Return: Always 0
 */
int myenv(state_t *state)
{
	print_list(state->env_list);
	return (0);
}

/**
 * mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 *
 * @state: the state of the shell
 *
 *  Return: 0 in success 1 otherwise
 */
int mysetenv(state_t *state)
{
	if (!state->argv[1]
	|| !state->argv[2])
	{
		write(2, "Incorrect number of arguements\n", 31);
		state->status = 1;
		return (1);
	}
	if (_setenv(state, state->argv[1], state->argv[2]))
	{
		state->status = 0;
		return (0);
	}

	state->status = 1;
	return (1);
}
