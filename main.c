#include "main.h"

/**
 * main - entry point
 * @count: number of args
 * @argv: arg vector
 * Return: 0 on success
 */
int main(int count, char **argv)
{
	info_t foo[] = { INFO_INIT };
	int i = 0;

	if (count == 2)
	{
		i = open(argv[1], O_RDONLY);
		if (i == -1)
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
		foo->readfd = i;
	}
	list_pop(foo);
	history_read(foo);
	loop(foo, argv);
	return (EXIT_SUCCESS);
}
