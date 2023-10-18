#include "main.h"

/**
 * search_path - search file between the path
 * @command: cmd
 * Return: cmd path
 */

char *search_path(char *command)
{
	const char *path = getenv("PATH");
	char *path_cpy = NULL;
	char *path_concat = NULL;
	char *result = NULL;
	char *token;
	struct stat info;

	if (stat(command, &info) == 0)
	{
		result = _strdup(command);
		return (result);
	}
	path_cpy = _strdup(path);
	token = strtok(path_cpy, ":");
	while (token != NULL)
	{
		int path_len = _strlen(token);

		if (token[path_len - 1] != '/')
		{
			path_concat = malloc(path_len + 2);
			_strcpy(path_concat, token);
			_strcat(path_concat, "/");
		}
		else
		{
			path_concat = _strdup(token);
		}
		strcat(path_concat, command);
		if (stat(path_concat, &info) == 0)
		{
			result = _strdup(path_concat);
			free(path_concat);
			break;
		}
		free(path_concat);
		token = strtok(NULL, ":");
	}
	free(path_cpy);
	return (result);
}
