/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:57:28 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/04/22 14:01:18 by gmaccha-         ###   ########.fr       */
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
	T_WORD,
	T_BUILTIN,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND, // >> -> si no existe lo crea y si existe lo agrega al final
	T_HEREDOC,
	T_INVALID,
}			t_token_type;

typedef struct s_status
{
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
	struct s_token	*next;
}				t_token;

typedef struct s_cmd
{
	t_token	*args;// Argumentos del comando
	t_token	*redir_in;// Redirecciones de entrada (<, <<)
	t_token	*redir_out;// Redirecciones de salida (>, >>)
}	t_cmd;

typedef struct s_cmds
{
	t_status	*status;
	char		*cmd_line;
	t_token		*token_lst;
	t_token		**piped_cmd; // comandos 
	t_token		*not_piped_cmd;
	t_cmd		**parsed_cmds; // listo para ejecucion
	t_cmd		*parsed_simple;
}				t_cmds;

#endif
