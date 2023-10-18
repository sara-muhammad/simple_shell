#include "main.h"

/**
 * execmd - execute command path, child process
 * @args: arguments
 * Return: exit status
 */

int execmd(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("Fork error");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        /*Child process*/
        if (execve(args[0], args, environ) == -1)
        {
            perror("Exec error");
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

    return (status);
}
