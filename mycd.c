#include "main.h"

/**
 * change_directory - Change directory and handle errors.
 *
 * @state: The state of the shell.
 * @dir: The directory to change to.
 *
 * Return: 0 on success, -1 on failure.
 */
int change_directory(state_t *state, const char *dir)
{
	int ret = chdir(dir);
	char buffer[1024];

	if (ret == -1)
	{
		print_error(state, "can't cd to ");
		write(2, dir, strlen(dir));
		write(2, "\n", 1);
		state->status = 2;
	}
	else
	{
		_setenv(state, "OLDPWD", _getenv(state, "PWD"));
		_setenv(state, "PWD", getcwd(buffer, 1024));
		state->status = 0;
	}
	return (ret);
}

/**
 * handle_dash_arg - Handle special case when argument is "-".
 *
 * @state: The state of the shell.
 * @old_str: The previous working directory.
 * @cwd_str: The current working directory.
 */
void handle_dash_arg(state_t *state, char *old_str, char *cwd_str)
{
	if (!old_str)
	{
		write(1, cwd_str, strlen(cwd_str));
		write(1, "\n", 1);
		state->status = 1;
	}
	else
	{
		write(1, old_str, strlen(old_str));
		write(1, "\n", 1);
		change_directory(state, old_str ? old_str : "/");
	}
}

/**
 * mycd - Changes the current directory of the process.
 *
 * @state: The state of the shell.
 *
 * Return: Always 0.
 */
int mycd(state_t *state)
{
	char *dir, buffer[1024];
	char *old_str = _getenv(state, "OLDPWD");

	if (!state->argv[1])
	{
		dir = _getenv(state, "HOME");
		if (!dir)
			dir = _getenv(state, "PWD") ? _getenv(state, "PWD") : "/";
		change_directory(state, dir);
	}
	else if (strcmp(state->argv[1], "-") == 0)
	{
		handle_dash_arg(state, old_str, getcwd(buffer, 1024));
	}
	else
	{
		change_directory(state, state->argv[1]);
	}

	return (0);
}
