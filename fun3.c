#include "shell.h"

/**
 * _execute - executes shell built-ins and external commands
 * @string_array: array of parsed input strings
 *
 * Return: nothing
 */
void _execute(char **string_array)
{
	int pid, status;
	char *full_path;
	void (*builtin_func)() = built_in_check(string_array);

	if (builtin_func != NULL)
		builtin_func();
	else if (_strcmp(string_array[0], "cd") == 0) /* for built-in cd command */
	{
		_cd(string_array);
	}
	else /* command is not a built-in */
	{
		full_path = path_check_f(string_array);
		if (full_path != NULL)
		{
			pid = fork();

			if (pid == 0) /* child process */
			{
				execve(full_path, string_array, environ);
				free(full_path);
				exit(EXIT_FAILURE);
			}
			if (pid > 0)
			{
				waitpid(pid, &status, 0);
				free(full_path);
			}
		}
		else
		{
			if (isatty(STDIN_FILENO))
				_printf("hsh: %s: command not found\n", string_array[0]);
			else
			{
				_printf("./hsh: 1: %s: not found\n", string_array[0]);
			}
		}
	}
}

/**
 * exit_shell - exits the shell program
 *
 * Return: nothing
 */
void exit_shell(void)
{
	exit(0);
}

/**
 * commentcheck - checks for # (comment) symbol
 * @str: string to check
 *
 * Return: returns string
 */
char *commentcheck(char *str)
{
	int i = 0, j;
	int len = _strlen(str);

	/* check for # (comment) in string, if not found return string */
	while (str[i] != '#')
	{
		if (str[i] == '\0')
		{
			return (str);
		}

		i++;
	}

	for (j = i; j < len; j++)
	{
		str[j] = '\0';
	}

	return (str);
}

/**
 * built_in_check - checks for built-in commands or functions
 * @s: array of parsed input strings
 *
 * Return: a pointer to the function if input matches, else NULL
 */
void (*built_in_check(char **s))(void)
{
	if (_strcmp(s[0], "exit") == 0)
	{
		return (exit_shell);
	}

	if (_strcmp(s[0], "env") == 0)
	{
		return (_env);
	}

	return (NULL);
}

/**
 * write_to_buff - writes characters to an array
 * @arr: The array of size BUFF(1024)
 * @c: the character to be written to the array
 *
 * Return: void
 */
void write_to_buff(char arr[BUFF_SIZE], char c)
{
	int i;

	for (i = 0; i < BUFF_SIZE; i++)
	{
		if (arr[i] == '\0')
		{
			arr[i] = c;
			return;
		}
	}
}
