#include "main.h"

/**
 * remove_comments - Remove Comments from string
 *
 * @str: string to parse
 *
 * Return: the new string
 */
char *remove_comments(char *str)
{
	char *com_loc;
	char *temp_str = _strdup(str);
	char **temp_line;

	if (!temp_str)
		return (NULL);

	com_loc = _strchr(temp_str, '#');
	if (!com_loc)
		return (temp_str);

	if (com_loc == temp_str)
	{
		temp_str[0] = '\n';
		temp_str[1] = '\0';
		return (temp_str);
	}

	if (*(--com_loc) != ' ')
		return (temp_str);

	temp_line = split(temp_str, "#");
	free(temp_str);

	if (!temp_line)
		return (NULL);

	temp_str = temp_line[0];

	free_array(temp_line, 1);

	return (temp_str);
}

/**
 * _strchr - locates a character in a string
 * @s: string to search
 * @c: character to find
 * Return: pointer to the first occurrence of the character c
 * in the string s, or NULL if the character is not found
 */

char *_strchr(char *s, char c)
{
	int i = 0;

	while (s[i] != '\0')
	{
		if (s[i] == c)
			break;
		i++;
	}

	if (s[i] == c)
		return (s + i);
	else
		return (NULL);
}
