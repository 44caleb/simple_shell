#include "shell.h"
/**
*main - a simple shell program
*Return: always 0 success
*/
int main(void)
{
	char *input = NULL;
	char *string_array[BUFF_SIZE];
	char cmd[BUFF_SIZE];

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			_printf("$$$ ");
			fflush(stdout);
		}

		input = get_input(cmd); /* get input and store in cmd buffer) */
		input = commentcheck(input);
		_split(input, string_array);
		_execute(string_array);
	}
	return (0);
}


/**
*_split - splits a string into substrings and stores each substring in a buffer
*@str: the string to be split
*@string_array: buffer where substrings are stored
*Return: nothing
*/
void _split(char *str, char **string_array)
{
	int i = 0, j = 0;
	char *ptr;

	if (str[i] != ' ') /* handle when first character is a white space*/
	{
		ptr = &str[0];
		string_array[j++] = ptr;
	}

	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == ':')
		{
			while (str[i + 1] == ' ') /* handle consecutive white space*/
			{
				str[i] = '\0';
				i++;
			}

			if (str[i + 1] == '\0')
			{
				break;
			}

			str[i] = '\0';
			i++;
			ptr = &str[i];
			string_array[j++] = ptr;
		}

		else
		{
			i++;
		}
	}
	string_array[j] = NULL;
}



/**
*get_input - gets input from stdin and stores in a buffer
*@cmd: buffer where stdin input is stored
*Return: the buffer
*/
char *get_input(char *cmd)
{
	char *input = NULL, *end;
	size_t input_size = 0;
	ssize_t bytes_read;

	bytes_read = getline(&input, &input_size, stdin);

	if (bytes_read == -1)
	{
		free(input);
		exit(0);
	}

	end = input + (bytes_read - 1);
	*end = '\0';

	_strcpy(cmd, input);
	free(input);
	return (cmd);
}


/**
*get_path_f - lists all the directories in the path vairable
*Return: returns a string showing all directories in the path variable
*/
char *get_path_f()
{
	int i = 0, j = 0, k = 5;
	char *path_variable = malloc(sizeof(char) * 400);

	while (environ[i] != NULL)
	{
		if (environ[i][0] == 'P' && environ[i][1] == 'A' &&
environ[i][2] == 'T' && environ[i][3] == 'H')
		{
			break;
		}
		i++;
	}

	while (environ[i][k] != '\0')
	{
		path_variable[j] = environ[i][k];
		j++;
		k++;
	}
	path_variable[j] = '\0';
	return (path_variable);
}


/**
*path_check_f - checks if a command is in a directory in the path variable
*@string_array: an array of strings. first string is command to check
*Return: the full path of the command, NULL if command does not exist
**/
char *path_check_f(char **string_array)
{
	int i = 0;

	char *path_variable = get_path_f();
	char **path_variables_array = malloc(sizeof(char *) * 300);

	_split(path_variable, path_variables_array);

	if (string_array[0][0] == '/' || string_array[0][0] == '.')
	{
		if (access(string_array[0], X_OK) == 0)
		{
			char *path = malloc(sizeof(char) * 200);

			_strcpy(path, string_array[0]);
			free(path_variable);
			free(path_variables_array);
			return (path);
		}
	}

	else
	{
		while (path_variables_array[i] != NULL)
		{
			char *full_path = add_slash_f(path_variables_array[i], string_array[0]);

			if (access(full_path, X_OK) == 0)
			{
				free(path_variable);
				free(path_variables_array);
				return (full_path);
			}

			free(full_path);
			i++;
		}
	}
	free(path_variable);
	free(path_variables_array);
	return (NULL);
}
