#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

int _strlen(char *s);
char *_strcpy(char *dest, char *src);
void execmd(char **argv);
int _putchar(char c);
void _puts(char *str);
int _strcmp(char *s1, char *s2);
char *get_location(char *command);
char *_strdup(const char *str);
char *_strcat(char *dest, char *src);
char *get_env(char *env_var);
void _envprint(void);

#endif
