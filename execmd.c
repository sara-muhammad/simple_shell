#include "main.h"
/**
  * execmd - execute a command
  * @argv: arguments passed
  */

void execmd(char **argv)
{
	char *command = NULL;
	char *r;
	char *eror;
	char *actual_command = NULL;
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		perror("Fork error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/*Child process*/
		command = argv[0];
		actual_command = get_location(command);

		if (execve(actual_command, argv, environ) == -1)
		{
			r = _strcat(command, ": 1");
			eror = _strcat(r, ": not found");
			perror(eror);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/*Parent process*/
		wait(&status);
		if (WIFEXITED(status))
		{
			status = WEXITSTATUS(status);
		}
	}

}
