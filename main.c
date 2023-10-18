#include "main.h"

/**
 * main - Entry point for a custom shell program.
 * @ac: Number of arguments (unused).
 * @av: Array of arguments, av[0] is the shell name.
 * Return: Shell exit status.
 */
int main(int ac, char **av)
{
	state_t state[] = {{NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0},
	{NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0}};

	(void) ac;
	state->shell_name = av[0];

	init_env_list(state);

	shell_loop(state);

	free_list(state->env_list);
	return (state->status);

}
