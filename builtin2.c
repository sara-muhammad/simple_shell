#include "main.h"

/**
 * _history - displays the history list, one command by line, preceded
 * @info: Structure containing potential arguments. Used to maintain
 *  Return: Always 0
 */
int _history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int _unsetalias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * _setalias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int _setalias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (_unsetalias(info, str));

	_unsetalias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @n: the alias node
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *n)
{
	char *p = NULL, *a = NULL;

	if (n)
	{
		p = _strchr(n->str, '=');
		for (a = n->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *  Return: Always 0
 */
int _alias(info_t *info)
{
	int j = 0;
	char *s = NULL;
	list_t *n = NULL;

	if (info->argc == 1)
	{
		n = info->alias;
		while (n)
		{
			print_alias(n);
			n = n->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		s = _strchr(info->argv[j], '=');
		if (s)
			_setalias(info, info->argv[j]);
		else
			print_alias(node_starts_with(info->alias, info->argv[j], '='));
	}

	return (0);
}
