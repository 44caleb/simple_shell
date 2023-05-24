#include "shell.h"

/**
 * add_slash_f - adds a slash between two strings
 * @str1: first string
 * @str2: second string
 *
 * Return: the new string
 */
char *add_slash_f(char *str1, char *str2)
{
	int len1, len2, i = 0, j = 0;
	char *new_string;

	len1 = _strlen(str1);
	len2 = _strlen(str2);
	new_string = malloc(sizeof(char) * (len1 + len2 + 2));

	if (new_string == NULL)
	{
		return (NULL);
	}

	while (str1[i] != '\0')
	{
		new_string[i] = str1[i];
		i++;
	}

	new_string[i++] = '/';

	while (str2[j] != '\0')
	{
		new_string[i++] = str2[j];
		j++;
	}

	new_string[i] = '\0';
	return (new_string);
}

/**
 * _strlen - counts the number of letters in a string
 * @str: string
 *
 * Return: the number of letters
 */
int _strlen(char *str)
{
	int len = 0;

	while (*str != '\0')
	{
		len++;
		str++;
	}
	return (len);
}

/**
 * _env - prints the environment variables
 *
 * Return: nothing
 */
void _env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		_printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * _strcmp - checks similarity of two strings
 * @str1: first string
 * @str2: second string
 *
 * Return: 0 (if similar), -1 (if different)
 */
int _strcmp(char *str1, char *str2)
{
	int i = 0;

	if (_strlen(str1) != _strlen(str2))
	{
		return (-1);
	}

	while (str1[i] != '\0')
	{
		if (str1[i] != str2[i])
		{
			return (-1);
		}
		i++;
	}
	return (0);
}

/**
 * _strcpy - copies a source string to a destination buffer
 * @destination: destination buffer
 * @source: source string
 *
 * Return: nothing
 */
void _strcpy(char *destination, char *source)
{
	int i = 0;

	while (source[i] != '\0')
	{
		destination[i] = source[i];
		i++;
	}

	destination[i] = '\0';
}







