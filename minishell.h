/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-07 12:08:41 by gmaccha-          #+#    #+#             */
/*   Updated: 2025-03-07 12:08:41 by gmaccha-         ###   ########.fr       */
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
# include <sys/time.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

# define RST	"\033[0m"
//# define RED	"\033[1;31m"
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
# define GREEN "\033[1;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[1;34m"
# define END "\033[0m"
# define CYAN "\033[1;36m"

#define HISTORY_FILE ".minishell_history"

typedef enum e_type {
	CMD,
	BUILTIN,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND, // >> -> si no existe lo crea y si existe lo agrega al final
	HEREDOC,
	SEMICOLON,
}			t_type;

typedef struct s_token
{
	char *value;
	t_type type;
	struct s_token	*next;
}				t_token;
/*
typedef struct s_process
{
	char				*local_env[32];
	char				*command;
	char				*argv[64];
	t_file				*input_file[16];
	t_file				*output_file[16];
	struct s_process	*next;
	struct s_process	*prev;
}						t_process;


typedef struct s_session
{
	t_ht_tab	*env;
	t_process	*process_lst;
	char		**envp;
	char		**child_envp;
	int			errcd;
	int			stat;
	int			std_fd[2];
}	t_session;


typedef struct s_cmds
{
	t_session	*session;
	char		*cmd_line;
	char		**cmd_splitted;
	t_token		**piped_cmd;
	t_token		*simple_cmd;
}	t_cmd_tab;

*/

void	print_header(void);
void	token_type(t_token *first);


#endif
