#include "main.h"

/**
 * print_error - prints an error message
 *
 * @state: the state of the shell
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(state_t *state, char *error)
{
	write(2, state->shell_name, _strlen(state->shell_name));
	write(2, ": ", 2);
	print_number(state->line_count, 2);
	write(2, ": ", 2);
	write(2, state->argv[0], _strlen(state->argv[0]));
	write(2, ": ", 2);
	write(2, error, _strlen(error));
}
