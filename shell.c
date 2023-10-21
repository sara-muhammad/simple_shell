#include "main.h"
#include "main2.h"
/**
 * loop - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int loop(info_t *info, char **av)
{
	ssize_t m = 0;
	int _ret = 0;

	while (m != -1 && _ret != -2)
	{
		_clear(info);
		if (interactive(info))
			_puts("$ ");
		e_putchar(BUF_FLUSH);
		m = get_input(info);
		if (m != -1)
		{
			_info(info, av);
			_ret = check_builtin(info);
			if (_ret == -1)
				search_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		info_free(info, 0);
	}
	write_history(info);
	info_free(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (_ret);
}

/**
 * check_builtin - finds a builtin command
 * @info: the parameter & return info struct
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully
 */
int check_builtin(info_t *info)
{
	int i, _ret = -1;
	builtin_table builtintbl[] = {
		{"exit", my_exit},
		{"env", _env},
		{"setenv", set_env},
		{"unsetenv", unset_env},
		{"help", _help},
		{"history", _history},
		{"cd", _cd},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			_ret = builtintbl[i].func(info);
			break;
		}
	return (_ret);
}

/**
 * search_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 * Return: void
 */
void search_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		forkcmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			forkcmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * forkcmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 * Return: void
 */
void forkcmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			info_free(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
