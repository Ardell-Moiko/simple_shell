#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 64

char *get_input(void);
char **parse_input(char *input);
int execute(char **args);
int check_builtin(char **args);
void handle_sigint(int sig);
char *get_input_file(FILE *file);
void cleanup(char **args, char *input);

#endif
