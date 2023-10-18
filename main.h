#ifndef _SHELL_H_
#define _SHELL_H_


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

extern char **environ;
#define READ_SIZE 1024

/**
 * struct list_s - singly linked list
 * @str: string
 * @index: the index of the node
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

/**
 * struct state_s - contains the state of the program
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ
 * @environ_changed: 1 if environ was changed
 * @status: the return status of the last exec'd command
 */
typedef struct state_s
{
	list_t *env_list;
	char **environ;
	char *line;
	char *shell_name;
	char *command;
	char **argv;
	int line_count;
	int environ_changed;
	int status;
	int exit_number;
} state_t;

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(state_t *);
} builtin_table;


/* String handlers */
char *_strdup(char *src);
char *_strcat(char *dest, char *src);
char *starts_with(const char *haystack, const char *needle);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strchr(char *s, char c);
char *_strtok(char *str, char *delim);
size_t count_split(char *str, char *delim);
char **split(char *str, char *delim);
char *remove_comments(char *str);


/* Environ handlers */
int init_env_list(state_t *state);
int _setenv(state_t *state, char *name, char *value);
int _unsetenv(state_t *state, char *name);
char *_getenv(state_t *state, const char *name);
char **get_environ(state_t *state);


/* Linked List handlers */
list_t *add_node_end(list_t **head, char *str);
size_t print_list(const list_t *h);
char **list_to_strings(list_t *head);
int delete_node_at_index(list_t **head, unsigned int index);
size_t list_len(const list_t *h);
void free_list(list_t *head);

/* Command Handlers */
char *locate_path(char *path_string, char *command);
int check_executable(char *file_path);
void execute_command(state_t *state);
int find_builtin(state_t *state);

/* Handle Error */
void print_error(state_t *state, char *error);
void print_number(int n, int fd);

/* Utils */
void free_array(char **array, int start);
void free_state(state_t *state);
void print_array(char **array);
int _atoi(char *s);

/* built in */
int myexit(state_t *state);
int myenv(state_t *state);
int mycd(state_t *state);
int mysetenv(state_t *state);
int myunsetenv(state_t *state);



/* Shell */
int shell_loop(state_t *state);
char *get_line(state_t *state);
char **get_commands(state_t *state);

#endif