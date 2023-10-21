#include "main.h"

/**
 * main - entry point
 * @count: number of args
 * @argv: arg vector
 * Return: 0 on success
 */
int main(int count, char **argv)
{
	info_t info[] = { INFO_INIT };
	int r = 0;

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
	list_pop(info);
	history_read(info);
	loop(info, argv);
	return (EXIT_SUCCESS);
}
