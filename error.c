#include "main.h"

/**
 *e_puts - prints an input string
 * @str: the string to be printed
 */
void e_puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	for (j = 0; str[j] != '\0'; j++)
	{
		e_putchar(str[j]);
	}
}

/**
 * put_fd - writes the input character to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
/**
 * e_putchar - writes the input character to stderr
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned.
 */
int e_putchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int j;

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}
/**
 * puts_fd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 * Return: the number of chars put
 */
int puts_fd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += put_fd(*str++, fd);
	}
	return (j);
}
