#include "main.h"

/**
 * _split - split string
 * @str: string
 * @sep: separator
 * Return: divided path
 */

char **_split(char *str, char *sep)
{
	char *token;
	char **split_str;
	int i = 0;
	int max_tokens = 100;

	split_str = (char **)malloc(max_tokens * sizeof(char *));
	if (!split_str)
	{
		free(split_str);
		return (NULL);
	}

	token = strtok(str, sep);
	while (token)
	{
		split_str[i] = token;
		i++;
		if (i >= max_tokens)
		{
			char **new_split_str;

			max_tokens += 100;
			new_split_str = (char **)malloc(max_tokens * sizeof(char *));
			if (!new_split_str)
			{
				free(split_str);
				return (NULL);
			}

			memcpy(new_split_str, split_str, i * sizeof(char *));
			free(split_str);
			split_str = new_split_str;
		}
		token = strtok(NULL, sep);
	}

	split_str[i] = NULL;
	return (split_str);
}
