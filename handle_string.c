#include "main.h"

char *_strdup(char *src)
{
    char *str;
    char *p;
    int len = 0;
	
	len = _strlen(src);

    str = malloc(len + 1);
	if (!str)
		return (NULL);

    p = str;
    while (*src)
        *p++ = *src++;

    *p = '\0';
    return str;
}

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
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
	if(!com_loc)
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

	return temp_str;
}