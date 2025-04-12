/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:57:28 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/04/12 12:48:48 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "./minishell.h"

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

typedef enum e_token_type // tipo de token
{
	TEXT,
	BUILTIN,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND, // >> -> si no existe lo crea y si existe lo agrega al final
	HEREDOC,
}			t_token_type;


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

typedef struct s_status
{
	//t_process	*process_lst;
	char		**envp;
	char		**child_envp;
	int			error_code;
	int			stat;
	int			std_fd[2];
}				t_status;

typedef struct s_token // clasificacion de los tokens
{
	char			*value;
	t_token_type	type;
	//struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_cmds
{
	t_status	*status;
	char		*cmd_line;
	t_token		*token_lst;
	char		**cmd_splitted;
	t_token		**piped_cmd;
	t_token		*not_piped_cmd;
}				t_cmds;


#endif
