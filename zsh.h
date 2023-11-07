#ifndef _ZSH_
#define _ZSH_

/*---LIBRARIES---*/
#include <sys/types.h>
#include <sys/sts.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <dirent.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <limits.h>

/*---MACROS---*/
#define ZSH_BUFSIZE 1024
#define ZSH_TOK_BUFSIZE 128
#define ZSH_TOK_DELIM " \t\r\n\a"

extern char **environ;

/**
 * struct data - struct containing runtime data for the zsh program.
 * @zsh_argv: argument vector.
 * @zsh_input: command line input.
 * @zsh_args: array of tokens of the command line.
 * @zsh_status: the exit status of the most recent zsh shell command.
 * @zsh_counter: line counter.
 * @zsh_envvars: environment variables.
 * @pid: process ID of the zsh shell.
 */
typedef struct data
{
	char **zsh_argv;
	char *zsh_input;
	char **zsh_args;
	int zsh_status;
	int zsh_counter;
	char **zsh_envvars;
	char *pid;
} zsh_shell;

/**
 * struct zsh_sep_t - singly linked list for zsh separators.
 * @separator: separator characters (; | &).
 * @next: next node in the list.
 * Description: single linked list to store separators.
 */
typedef struct zsh_sep_t
{
	char separator;
	struct zsh_sep_t *next;
} zsh_sep_t;

/**
 * struct zsh_var_t - singly linked list for zsh variables.
 * @zsh_var_len: length of variable.
 * @value: variable value.
 * @val_len: value length.
 * @next: pointer to the next node in the list.
 * Description: single linked list to store variables.
 */
typedef struct zsh_var_t
{
	int zsh_var_len;
	char *value;
	int val_len;
	struct zsh_var_t *next;
} zsh_var_t;

/**
 * struct zsh_cmdln_t - singly linked list for zsh command lines.
 * @line: the command line.
 * @next: next node in the list.
 * Description: singly linked list to store command lines.
 */
typedef  struct zsh_cmdln_t
{
	char *line;
	struct zsh_cmdln_t *next;
} zsh_cmdln_t;

/**
 * struct builtin_t - struct containing builtin commands.
 * @name: name of the builtin command (cd, ls, env).
 * @f: pointer to the associated function.
 */
typedef struct builtin_t
{
	char *name;
	int (*f)(zsh_zsh_shell *datash);
} builtin_t;

/*---PROTOTYPES---*/
/* zsh_str1.c */
char *zsh_strcat(char *dest, const char *src);
char *zsh_strcpy(char *dest, const char *src);
int zsh_strcmp(const char *str1, const char *str2);
char *zsh_strchr(const char *str, char c);
int zsh_strspn(const char *str, const char *accept);

/* zsh_str2.c */
char *zsh_strdup(const char *str);
int zsh_strlen(const char *str);
int zsh_charcmp(char str[], const char *delim);
char *zsh_strtok(char str[], const char *delim);
int zsh_isdigit(const char *str);

/* zsh_mem1.c */
void zsh_memcpy(void *dest, const void *src, size_t size);
void *zsh_realloc(void *ptr, size_t old_size, size_t new_size);
char **zsh_reallocdp(char **ptr, size_t old_size, size_t new_size);
void zsh_rev_string(char *str);

/* zsh_lists1.c */
zsh_sep_t *zsh_add_sep_node(zsh_sep_t **head char sep);
void zsh_free_sep(zsh_sep_t **head);
zsh_cmdln_t *zsh_add_line_node(zsh_cmdln_t **head, char *line);
void zsh_free_line(zsh_cmdln_t **head);

/* zsh_lists2.c */
zsh_var_t *zsh_add_rvar_node(zsh_var_t **head, int lvar, char *var, int lval);
void zsh_free_rvar(zsh_var_t **head);

/* zsh_split.c */
char *zsh_swap_char(char *input, int bool);
void zsh_add_nodes(zsh_sep_t **head_s, zsh_cmdln_t **head_l, char *input);
void zsh_go_next(zsh_sep_t **list_s, zsh_cmdln_t **list_l, zsh_shell *datash);
int zsh_split_command(zsh_shell *datash, char *input);
char **zsh_split_line(char *input);

/* zsh_syntax.c */
int zsh_repeat_char(const char *input, int z);
int zsh_sep_op(const char *input, int z, char last);
int zsh_first_char(const char *input, int *z);
void zsh_print_error(zsh_shell *datash, const char *input, int z, int bool);
int zsh_check_error(zsh_shell *datash, const char *input);

/* zsh_shell.c */
char *zsh_without_comment(const char *z);
void zsh_loop_shell(zsh_shell *datash);
int zsh_cd_shell(zsh_shell *datash);
int zsh_exit_shell(zsh_shell *datash);
int (*zsh_get_builtin(const char *cmd))(zsh_shell *datash);

/* zsh_var.c */
void zsh_check_env(zsh_var_t **head, char *z, zsh_shell *datash);
int zsh_check_vars(zsh_var_t **head, char *z, char *y, zsh_shell *data);
char *zsh_rep_input(zsh_var_t **head, char *input, char *new_input, int nlen);
char *zsh_rep_var(char *input, zsh_shell *datash);

/* zsh_line.c */
char *zsh_read_line(int *i_eof);
int zsh_exec_line(zsh_shell *datash);
void zsh_bring_line(char **lineptr, size_t *s, char *buffer, size_t t);
ssize_t zsh_get_line(char **lineptr, size_t *s, FILE *stream);
char *zsh_copy_info(const char *name, const char *value);

/* zsh_exec.c */
int zsh_is_cdir(const char *path, int *z);
char *zsh_which(const char *cmd, char **zsh_envvars);
int zsh_is_exec(zsh_shell *datash);
int zsh_error_cmd(const char *dir, zsh_shell *datash);
int zsh_cmd_exec(zsh_shell *datash);

/* zsh_env.c */
char zsh_getenv(const char *name, char **zsh_envvars);
int zsh_env(zsh_shell *datash);
void zsh_set_env(const char *name, const char *value, zsh_shell *datash);
int zsh_setenv(zsh_shell *datash);
int zsh_unsetenv(zsh_shell *datash);

/* zsh_chdir.c */
void zsh_cd_dot(zsh_shell *datash);
void zsh_cd_to(zsh_shell *datash);
void zsh_cd_previous(zsh_shell *datash);
void zsh_cd_to_home(zsh_shell *datash);

/* zsh_stdlib.c */
int zsh_get_len(int n);
char *zsh_itoa(int n);
int zsh_atoi(const char *s);
void zsh_get_sigint(int sig);

/* zsh_error1.c */
char *zsh_strcat(zsh_shell *, const char *, const char *, const char *);
char *zsh_getcd_err(zsh_shell *datash);
char *zsh_notfound_err(zsh_shell *datash);
char *zsh_exit_err(zsh_shell *datash);
int zsh_get_err(zsh_shell *datash, int eval);

/* zsh_error2.c */
char *zsh_alias_err(const char **args);
char *zsh_env_err(zsh_shell *datash);
char *zsh_syntax_err(const char **args);
char *zsh_perm_err(const char **args);
char *zsh_path126_err(zsh_shell *datash);

/* zsh_help1.c */
void zsh_help_env(void);
void zsh_help_setenv(void);
void zsh_help_unsetenv(void);
void zsh_help_general(void);
void zsh_help_exit(void);

/* zsh_help2.c */
void zsh_help(void);
void zsh_help_alias(void);
void zsh_help_cd(void);
int zsh_get_help(zsh_shell *datash);

#endif
