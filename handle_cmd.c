#include "main.h"

/**
 * execute_command - executs a command
 *
 * @state: the state of the shell
 * @path: the path to the command
 * @command: the command
 *
 * Return: void
 */
void execute_command(state_t *state)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(state->command, state->argv, get_environ(state)) == -1)
		{
			free_state(state);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(state->status));
		if (WIFEXITED(state->status))
		{
			state->status = WEXITSTATUS(state->status);
		}
	}
}


/**
 * locate_path - finds this cmd in the PATH string
 *
 * @state: the info struct
 * @path_string: the PATH string
 * @command: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *locate_path(state_t *state, char *path_string, char *command)
{
	char **tokens, *full_path;
	int i;


	if (!path_string || !command)
		return (NULL);

	if ((starts_with(command, ".") || starts_with(command, "/"))
	&& check_executable(command))
		return _strdup(command);

	tokens = split(path_string, ":");

	for (i = 0; tokens[i]; i++)
	{
		full_path = malloc(strlen(tokens[i]) + strlen(command) + 2);
		if (full_path == NULL)
			continue;

		strcpy(full_path, tokens[i]);
		_strcat(full_path, "/");
		_strcat(full_path, command);

		if (check_executable(full_path))
		{
			free_array(tokens, 0);
			return full_path;
		}

		free(full_path);
	}


	free_array(tokens, 0);

	return (NULL);
}

/**
 * find_builtin - finds a builtin command
 *
 * @state: the info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(state_t *state)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", myexit},
		{"env", myenv},
		{"cd", mycd},
		{"setenv", mysetenv},
		{"unsetenv", myunsetenv},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(state->argv[0], builtintbl[i].type) == 0)
		{
			state->command = _strdup(state->argv[0]);
			built_in_ret = builtintbl[i].func(state);
			break;
		}
	return (built_in_ret);
}

/**
 * check_executable - determines if a file is an executable command
 * @file_path: path to the file
 *
 * Return: (1) if true, (0) otherwise
 */
int check_executable(char *file_path)
{
	struct stat file_stat;

	if (!file_path || stat(file_path, &file_stat))
		return (0);

	if (file_stat.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
