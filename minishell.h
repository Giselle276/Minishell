/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:08:41 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/03/27 17:11:05 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <pthread.h>
# include <signal.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"
# include "shell.h"

# define RST	"\033[0m"
# define G		"\033[1;32m"
#define  Y		"\033[38;2;252;255;166m"
# define B		"\033[1;34m"
# define M		"\033[1;35m"
# define C		"\033[1;36m"
# define W		"\033[1;37m"
# define S      "\033[38;5;147m"
#define USER_M		"\033[38;2;193;255;215m"
#define BABY_BLUE		"\033[38;2;177;240;247m"

# define RED "\033[0;31m"
#define DARK_PINK "\033[38;2;189;30;30m"
#define LIGHT_PINK "\033[38;2;216;131;115m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[1;34m"
# define END "\033[0m"
# define CYAN "\033[1;36m"

typedef enum e_errcode // codigos de error
{
	SIGEXIT,
	ESYNTAX,
	EUSAGE,
	EPARSE,
	EUNFQT,
	EMPTYLINE,
	ECOMMAND,
	ENUMARG,
	EALLOC,
	ECMDNF = 127, // command not found
	SIGNT = 130, // control c signal interrupt
	SQUIT = 131, //  ctrl + \ no deberia hacer nada
	EEOF,
	__ERRMAX
}					t_errcode;

typedef enum e_type // tipo de token
{
	TEXT,
	BUILTIN,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND, // >> -> si no existe lo crea y si existe lo agrega al final
	HEREDOC,
	SEMICOLON,
}			t_type;

typedef struct s_token // clasificacion de los tokens
{
	char *value;
	t_type type;
	struct s_token	*next;
}				t_token;
// flags [2: O_RDONLY |1: WRONLY CREAT APPEND| 0: WRONLY CREAT TRUNC]
typedef struct s_file // estructura de los archivos
{
	char				*path;
	int					flags;
	int					fd;
}						t_file;

typedef struct s_process // estructura de los procesos
{
	char				*local_env[32];
	char				*command;
	char				*argv[64];
	t_file				*input_file[16];
	t_file				*output_file[16];
	struct s_process	*next;
	struct s_process	*prev;
}						t_process;

typedef struct s_hash_item // estructura de los items
{
	char	*key;
	char	*value;
	bool	is_env;
}	t_hash_item;

//  Double linked list
typedef struct s_double_list
{
	t_hash_item				*item;
	struct s_double_list	*next;
	struct s_double_list	*prev;
}	t_double_list;

typedef struct s_hash_tab
{
	t_hash_item	**items;
	t_double_list	**overflow_buckets;
	int			size;
	int			count;
}	t_hash_tab;



void		print_header(void);
//void		token_type(t_token *first);
//t_process	*parser(t_cmd_tab *tb);
//t_process	*simple_or_piped(t_token **tokens, int flag);
//t_process	*parse_command(t_token **tokens);
//void 		push_process(t_process **lst, t_process *new_process);
//int 		validate_input(const char *input);
//char		*get_path(char *cmd);
//void		execute_command(char *cmd, char **args);
//void 		parse_input(char *input, char **args);
//void		clean_shell(shell_status);
//t_hash_tab	*load_env(char *envp[]);
//error
void		error_exit(t_errcode err_type);

#endif
