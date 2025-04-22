/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:08:41 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/04/16 11:40:49 by gmaccha-         ###   ########.fr       */
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
# include "./structs.h"
# include "./shell.h"
# include "./tokens.h"


# define RST	"\033[0m"
# define G		"\033[1;32m"
# define Y		"\033[38;2;252;255;166m"
# define B		"\033[1;34m"
# define M		"\033[1;35m"
# define C		"\033[1;36m"
# define W		"\033[1;37m"
# define S      "\033[38;5;147m"
# define USER_M		"\033[38;2;193;255;215m"
# define BABY_BLUE		"\033[38;2;177;240;247m"

# define T_SQUOTE	'\''
# define T_DQUOTE	'"'
# define T_ESCAPE	'\\'
# define T_PIPE		'|'
# define T_LESS		'<'
# define T_GREATER	'>'
# define T_SMCOLON	';'
# define T_SPACE	' '

# define RED "\033[0;31m"
# define DARK_PINK "\033[38;2;189;30;30m"
# define LIGHT_PINK "\033[38;2;216;131;115m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[1;34m"
# define END "\033[0m"
# define CYAN "\033[1;36m"

/*typedef enum e_errcode // codigos de error
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
}						t_process;*/

void		print_header(void);
//t_process	*simple_or_piped(t_token **tokens, int flag);
//int 		validate_input(const char *input);
//char		*get_path(char *cmd);
//void		clean_shell(shell_status);

#endif
