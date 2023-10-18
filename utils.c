#include "main.h"

void free_array(char **array, int start)
{
	for (int i = start; array[i] != NULL; i++)
	{
		free(array[i]);
	}

	free(array);
}

void print_array(char **array)
{
	for (int i = 0; array[i] != NULL; i++)
	{
		printf("[%d] -> %s", i, array[i]);
	}
}

void free_state(state_t *state)
{
	if (state == NULL)
		return;

	if (state->argv)
	{
		free_array(state->argv, 0);
		state->argv = NULL;
	}

	if (state->environ)
	{
		free_array(state->environ, 0);
		state->environ = NULL;
	}

	if (state->command)
	{
		free(state->command);
		state->command = NULL;
	}

	if (state->line)
	{
		free(state->line);
		state->line = NULL;
	}
}

/**
 * _atoi - converts a string to an integer
 * 
 * @s: the string to be converted
 *
 * Return: number, -1 if error
 */
int _atoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_number - Function that prints any given number using _putchar
 *
 * @n: number to print
 * @fd: the file discreptor
 *
 * Return: void, this function doesn't return any value
 */

void print_number(int n, int fd)
{
	unsigned int temp = n;
	char digit;

	if (n < 0)
	{
		write(fd, "-", 1);
		temp = -n;
	}

	if (temp >= 10)
		print_number(temp / 10, fd);

	digit = temp % 10 + '0';
	write(fd, &digit, 1);
}