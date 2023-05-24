#include "shell.h"

/**
 * get_home - gets the home directory
 *
 * Return: home directory string
 */
char *get_home(void)
{
	int i = 0, j = 5, k = 0;
	char *home = NULL;

	while (environ[i] != NULL)
	{
		if (environ[i][0] == 'H' && environ[i][1] == 'O' &&
environ[i][2] == 'M' && environ[i][3] == 'E')
		{
			break;
		}
		i++;
	}

	home = malloc(sizeof(char) * 200);

	while (environ[i][j] != '\0')
	{
		home[k] = environ[i][j];
		j++;
		k++;
	}

	home[k] = '\0';
	return (home);
}

/**
 * _cd - changes directory
 * @string_array: array of strings where the 2nd element is the directory path
 */
void _cd(char **string_array)
{
	char *home = NULL;

	if (string_array[1] == NULL)
	{
		home = get_home();
		chdir(home);
		free(home);
		return;
	}

	if (access(string_array[1], F_OK) != 0)
	{
		_printf("hsh: cd: %s: No such file or directory\n", string_array[1]);
		return;
	}

	chdir(string_array[1]);
}
