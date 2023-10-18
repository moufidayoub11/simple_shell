#include "main.h"

int main(int ac, char **av)
{
	state_t state[] = {{ NULL, NULL, NULL, NULL, NULL, NULL, 0, 0 , 0, 0 },
	{NULL, NULL, NULL, NULL, NULL, NULL, 0, 0 , 0, 0 }};

	(void) ac;
	state->shell_name = av[0];

	init_env_list(state);

	shell_loop(state);

	free_list(state->env_list);
	return (state->status);

}
