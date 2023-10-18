#include "main.h"

/**
 * main - open shell, project base
 * Return: int
 */

int main(void)
{
	char *buff = NULL, **args;
	size_t read_size = 0;
	ssize_t bizoo = 0;
	int exit_status = 0;

	while (1)
	{
		if (isatty(0))
			_puts("hsh$ ");

		bizoo = getline(&buff, &read_size, stdin);
		if (bizoo == -1 || _strcmp("exit\n", buff) == 0)
		{
			free(buff);
			break;
		}
		buff[bizoo - 1] = '\0';

		if (_strcmp("env", buff) == 0)
		{
			_envprint();
			continue;
		}

		if (blank_line(buff) == 1)
		{
			exit_status = 0;
			continue;
		}

		args = _split(buff, "\t\n");
		args[0] = search_path(args[0]);

		if (args[0] != NULL)
			exit_status = execmd(args);
		else
			perror("Error");
		free(args);
	}
	return (exit_status);
}
