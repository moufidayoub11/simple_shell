#include "main.h"

/**
 * split - splits a string using a delimiter
 *
 * @str: string to tokenize
 * @delim: delimiter
 *
 * Return: array of tokens
 */

char **split(char *str, char *delim)
{
	int i = 0;
	size_t tokens_size = 0;
	char **tokens = NULL;
	char *token = NULL;
	char *temp = _strdup(str);

	if (str == NULL)
		return (NULL);

	tokens_size = count_split(str, delim);

	tokens = malloc(sizeof(char *) * tokens_size);
	if (tokens == NULL)
		return (NULL);

	token = strtok(temp, delim);
	while (token != NULL)
	{
		tokens[i] = _strdup(token);
		token = strtok(NULL, delim);
		i++;
	}

	tokens[i] = NULL;
	free(temp);
	return (tokens);
}


/**
 * count_split - counts how many words splited
 * @str: string to tokenize
 * @delim: delimiter
 * Return: count
 */

size_t count_split(char *str, char *delim)
{
	size_t count = 1;
	char *temp = _strdup(str);
	char *token = NULL;

	if (str == NULL)
		return (0);

	token = strtok(temp, delim);
	while (token != NULL)
	{
		token = strtok(NULL, delim);
		count++;
	}

	free(temp);
	return (count);
}

/**
 * _strtok - tokenizes a string
 * @str: string to tokenize
 * @delim: delimiter
 * Return: pointer to the first token found
 */

char *_strtok(char *str, char *delim)
{
	static char *token;
	static char *next;
	char *delim_ptr;

	if (str != NULL)
		next = str;
	if (next == NULL)
		return (NULL);
	token = next;
	delim_ptr = _strchr(token, *delim);

	if (delim_ptr != NULL)
	{
		*delim_ptr = '\0';
		next = delim_ptr + 1;
	}
	else
		next = NULL;
	return (token);
}
