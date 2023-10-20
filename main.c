#include "main.h"

/**
 * main - entry point
 * @ac: number of args
 * @av: arg vector
 * Return: 0 on success
 */
int main(int count, char **argv)
{
	info_t info[] = { INFO_INIT };
	int r = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (r)
		: "r" (r));

	if (count == 2)
	{
		r = open(argv[1], O_RDONLY);
		if (r == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				e_puts(argv[0]);
				e_puts(": 0: Can't open file ");
				e_puts(argv[1]);
				e_putchar('\n');
				e_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = r;
	}
	populate_env_list(info);
	read_history(info);
	loop(info, argv);
	return (EXIT_SUCCESS);
}
