#include "main.h"


/**
 * shell_loop - main shell loop
 *
 * @state: the state of the shell
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_loop(state_t *state)
{
	int built_in_ret = -1;

	signal(SIGINT, sigint_handler);
	while (1)
	{
		if (get_line(state) == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 2);
			break;
		}
		state->line_count++;
		if (get_commands(state) == NULL)
		{
			if (state->argv[0])
			{
				built_in_ret = find_builtin(state);
				if (built_in_ret != -1)
				{
					if (built_in_ret == -2)
					{
					if (state->exit_number != -1)
						state->status = state->exit_number;
					break;
					}
				}
				else
				{
					print_error(state, "not found\n");
					state->status = 127;
				}
			}
			free_state(state);
			continue;
		}
		execute_command(state);
		free_state(state);
	}
	free_state(state);
	return (state->status);
}

/**
 * get_commands - Set the line property in state
 *
 * @state: the state of the shell
 *
 * Return: the line in state, NULL if failed
 */
char **get_commands(state_t *state)
{
	char **argv;
	char *command;

	if (!state->line)
		return (NULL);

	argv = split(state->line, " \t\n");
	if (!argv)
		return (NULL);

	state->argv = argv;

	command = locate_path(_getenv(state, "PATH"), argv[0]);

	if (!command)
	{
		return (NULL);
	}
	state->command = command;

	return (state->argv);
}


/**
 * get_line - Set the line property in state
 *
 * @state: the state of the shell
 *
 * Return: the line in state, NULL if failed
 */
char *get_line(state_t *state)
{
	int r;
	char *real_line;
	size_t line_size = 0;

	if (isatty(STDIN_FILENO))
	{
		fflush(stdin);
		write(STDOUT_FILENO, "$ ", 2);
	}

	r = getline(&state->line, &line_size, stdin);

	if (r == EOF)
		return (NULL);

	if (state->line[r - 1] == '\n')
		state->line[r - 1] = '\0';

	real_line = remove_comments(state->line);
	if (!real_line)
		return (NULL);

	free(state->line);

	state->line = real_line;

	return (real_line);
}

/**
 * sigint_handler - handles the signal SIGINT
 * @signal: signal to handle
 */

void sigint_handler(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n$ ", 3);
}
