#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <errno.h>

#define BUFF_SIZE 1024


void write_to_buff(char arr[BUFF_SIZE], char c);
int _printf(const char *format, ...);
int print_str(va_list args, char arr[BUFF_SIZE]);
char *_getline(int fd);
void _split(char *str, char **string_array);
char *get_input(char *cmd);
char *get_path_f();
char *path_check_f(char **string_array);
char *add_slash_f(char *str1, char *str2);
int _strlen(char *str);
void _env(void);
int _strcmp(char *str1, char *str2);
void _strcpy(char *destination, char *source);
void _execute(char **string_array);
char *commentcheck(char *str);
void (*built_in_check(char **s))();
void exit_shell(void);
void _cd(char **string_array);
char *get_home(void);

extern char **environ;

#endif
