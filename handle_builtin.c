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
 * mycd - changes the current directory of the process
 *
 * @state: the state of the shell
 *
 *  Return: Always 0
 */
int mycd(state_t *state)
{
	char *cwd_str, *dir, buffer[1024];
	int chdir_ret;
	char *old_str = _getenv(state, "OLDPWD");

	cwd_str = getcwd(buffer, 1024);
	if (!cwd_str)
		perror("Error: ");

	if (!state->argv[1])
	{
		dir = _getenv(state, "HOME");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenv(state, "PWD")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(state->argv[1], "-") == 0)
	{
		if (!old_str)
		{
			write(1, cwd_str, _strlen(cwd_str));
			write(1, "\n", 1);
			state->status = 1;
			return (1);
		}
		write(1, old_str, _strlen(old_str));
		write(1, "\n", 1);
		chdir_ret =
			chdir(old_str ? old_str : "/");
	}
	else
		chdir_ret = chdir(state->argv[1]);
	
	if (chdir_ret == -1)
	{
		print_error(state, "can't cd to ");
		write(2, state->argv[1], _strlen(state->argv[1]));
		write(2, "\n", 1);
		state->status = 2;
	}
	else
	{
		_setenv(state, "OLDPWD", _getenv(state, "PWD"));
		_setenv(state, "PWD", getcwd(buffer, 1024));
		state->status = 0;
	}
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


/**
 * _myunsetenv - Remove an environment variable
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