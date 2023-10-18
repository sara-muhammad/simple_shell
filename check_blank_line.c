#include "main.h"

/**
 * blank_line - checks if exists a empty line
 * @buffer: line
 * Return: 0 or 1 (int)
 */

int blank_line(char *buffer)
{
	int j;

	while (buffer)
	{
		if (buffer[j] != ' ')
			return (0);
		j++;
	}
	return (1);
}
