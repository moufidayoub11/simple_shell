#include "main.h"

int main(int ac, char **av)
{
	state_t state[] = STATE_INIT;

	state->shell_name = av[0];

	init_env_list(state);

	shell_loop(state);

	free_list(state->env_list);
	return (state->status);

}
