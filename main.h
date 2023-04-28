#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define END_OF_FILE -2
#define EXIT -3

extern char **environ;
int hist;
char *name;

/**
 * struct builtin_s - defines builtin commands of shell
 * @name: the builtin command name.
 * @f: points to the builtin command's function
 */
typedef struct builtin_s
{
char *name;
int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct list_s - defines a linked list.
 * @dir: directory path.
 * @next: points to another struct list_s.
 */
typedef struct list_s
{
char *dir;
struct list_s *next;
} list_t;

/**
 * struct alias_s - A struct that defines aliases.
 * @name: the alias name.
 * @value: the alias value.
 * @next: points to another struct alias_s.
 */
typedef struct alias_s
{
char *name;
char *value;
struct alias_s *next;
} alias_t;

alias_t *aliases;

void handle_sigint(int sig);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);


int argument_check(char **args);
void free_args(char **args, char **front);
char **alias_replace(char **args);
void line_handler(char **line, ssize_t read);
void replace_var(char **args, int *exe_ret);
char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int arguments_handler(int *exe_ret);

char *g_locate(char *command);
list_t *dir_path(char *path);
int execute(char **args, char **front);
void free_list(list_t *head);
char *_itoa(int num);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_myrealloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_mystrtok(char *line, char *delim);

int create_error(char **args, int err);
char *handle_errors_env(char **args);
char *handle_errors_1(char **args);
char *handle_errors_2_cd(char **args);
char *handle_errors_2_syntax(char **args);
char *handle_errors_126(char **args);
char *handle_errors_127(char **args);
char *handle_errors_2_exit(char **args);

int _mystrlen(const char *s);
char *_mystrcat(char *dest, const char *src);
char *_mystrncat(char *dest, const char *src, size_t n);
char *_mystrcpy(char *dest, const char *src);
char *_mystrchr(char *s, char c);
int _mystrspn(char *s, char *accept);
int _mystrcmp(char *s1, char *s2);
int _mystrncmp(const char *s1, const char *s2, size_t n);

int (*get_builtin(char *command))(char **args, char **front);
int byshell_exit(char **args, char **front);
int byshell_cd(char **args, char __attribute__((__unused__)) **front);
int byshell_alias(char **args, char __attribute__((__unused__)) **front);
int byshell_help(char **args, char __attribute__((__unused__)) **front);
int byshell_env(char **args, char __attribute__((__unused__)) **front);
int byshell_setenv(char **args, char __attribute__((__unused__)) **front);
int byshell_unsetenv(char **args, char __attribute__((__unused__)) **front);

alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *end_node_add(list_t **head, char *dir);
void free_list(list_t *head);

void linked_help_env(void);
void linked_help_setenv(void);
void linked_help_unsetenv(void);
void linked_help_history(void);
void linked_help_all(void);
void linked_help_alias(void);
void linked_help_cd(void);
void linked_help_exit(void);
void linked_help_help(void);

int file_process_comnds(char *file_path, int *exe_ret);

char **copy_env(void);
void free_env(void);
char **_my_getenv(const char *var);
#endif

