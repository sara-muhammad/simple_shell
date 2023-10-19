#include "main.h"
/**
 * _hash - handle comments
 * @buff: pointer to user input
 * Return: 0 or 1
 */
int _hash(char *buff)
{
	int i = 0, j;

	while (buff[i])
	{
		if (buff[0] == 'e' && buff[1] == 'c' && buff[2] == 'h' && buff[3] == 'o' && buff[4] == ' ')
		{
			for (j = 5; buff[j] != '#'; j++)
			{
				_putchar(buff[j]);
			}
			_putchar('\n');
			return (0);
		}
		else
		{
			if (buff[i] == '#')
				return (0);
		}
		i++;
	}
	return (1);
}
