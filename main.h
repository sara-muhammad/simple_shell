#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *arg;
	char **argv;
	char *path;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/* file-io._c */
int history_read(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int history_read(info_t *info);
char *get_history_file(info_t *info);
int write_history(info_t *info);
/* liststring.c module */
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
/* liststring2.c module */
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
/* ch.c */
int _replacevars(info_t *);
int _replace(char **, char *);
int _chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int _replacealias(info_t *);
/* shell.c */
void search_cmd(info_t *);
void forkcmd(info_t *);
int loop(info_t *, char **);
int check_builtin(info_t *);
/* get_path.c */
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
int is_cmd(info_t *, char *);
/* loophsh.c */
int loophsh(char **);
/* error.c */
void e_puts(char *);
int puts_fd(char *str, int fd);
int e_putchar(char);
int put_fd(char c, int fd);
/* strings1.c */
int _strlen(char *);
char *_strcat(char *, char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
/* strings2.c */
void _puts(char *);
int _putchar(char);
char *_strcpy(char *, char *);
char *_strdup(const char *);
/* strings3.c */
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);
char *_strncat(char *, char *, int);
/* more strings.c */
char **str_to_w(char *, char *);
char **str_to_w2(char *, char);
/* memory.c */
void *_realloc(void *, unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);
void ffree(char **);
/* memory2.c */
int bfree(void **);
/* helper_funcs.c */
int _isalpha(int);
int _atoi(char *);
int interactive(info_t *);
int is_delim(char, char *);
/* helper_funcs2.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
/* builtin.c */
int _cd(info_t *);
int _help(info_t *);
int my_exit(info_t *);
/* builtin2.c */
int _setalias(info_t *info, char *str);
int _unsetalias(info_t *info, char *str);
int _history(info_t *);
int _alias(info_t *);
/*get_line.c module*/
void sigintHandler(int);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
/* param.c module */
void info_free(info_t *, int);
void _clear(info_t *);
void _info(info_t *, char **);
/* enviroment.c module */
int _env(info_t *);
int set_env(info_t *);
char *_getenv(info_t *, const char *);
int unset_env(info_t *);
int list_pop(info_t *);
/* enviroment2.c module */
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char **get_environ(info_t *);

extern char **environ;

#endif
