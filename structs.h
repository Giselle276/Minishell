/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:57:28 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/05/16 16:51:47 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "./minishell.h"

typedef enum e_errcode
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
	ECMDNF = 127,
	SIGNT = 130,
	SQUIT = 131,
	EEOF,
	__ERRMAX
}					t_errcode;

typedef enum e_token_type
{
	T_WORD,
	T_BUILTIN,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	T_INVALID,
}			t_token_type;

typedef struct s_status
{
	char		**envp;
	char		**child_envp;
	int			error_code;
	int			stat;
	int			signal_interrupted;
}				t_status;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	char			quote_type;
}				t_token;

typedef struct s_cmd
{
	t_token	*args;
	t_token	*redir_in;
	t_token	*redir_out;
}	t_cmd;

typedef struct s_cmds
{
	char		*cmd_line;
	t_token		*token_lst;
	t_token		**piped_cmd;
	t_token		*not_piped_cmd;
	t_cmd		**parsed_cmds;
	t_cmd		*parsed_simple;
}				t_cmds;


#endif
