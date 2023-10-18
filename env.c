#include "main.h"

/**
 * get_env - get env variables
 * @env_var: env variable
 * Return: env variable result, its content
 */

char *get_env(char *env_var)
{
	int i = 0, j =0;
	int match;

	while (environ[i])
	{
		match = 1;

		while (environ[i][j] != '=' && env_var[j] != '\0')
		{
			if (environ[i][j] != env_var[j]) 
			{
                match = 0;
                break;
            }
            j++;
		}
		if (match == 1 && environ[i][j] == '=') 
		{
            return &(environ[i][j + 1]);
		}
		i++;
	}
	return (NULL);
}

/**
 * _envprint - prints environment
*/
void _envprint(void)
{
	int i = 0;

	while (environ[i])
	{
		_puts(environ[i]);
		_putchar('\n');
		i++;
	}
}