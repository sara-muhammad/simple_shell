#include "main.h"
/**
 * main - entry point
 * Return: 0 on success, 1 on error
 */
int main(void)
{
	char *lineptr, *token;
	size_t n = 0;
	ssize_t read;
	const char *delim = " \n";
	int i;
	char **argv;

	while (1)
	{
		isatty(0);
		write(1, "Shell$ ", 7);
		read = getline(&lineptr, &n, stdin);
		if (read == -1 || _strcmp("exit\n", lineptr) == 0)
		{
			break;
		}
		argv = malloc(sizeof(char *) * 1024);
		token = strtok(lineptr, delim);
		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * _strlen(token));
			_strcpy(argv[i], token);
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;
		execmd(argv);
	}
	free(lineptr);
	return (0);
}
