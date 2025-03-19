/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42madrid.com>           #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-18 13:51:43 by cgil              #+#    #+#             */
/*   Updated: 2025-03-18 13:51:43 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SHELL_H
#define SHELL_H

#include "minishell.h"

typedef struct s_status
{
	t_hash_tab	*env;
	t_process	*process_lst;
	char		**envp;
	char		**child_envp;
	int			errcd;
	int			stat;
	int			std_fd[2];
}				t_status;

typedef struct s_cmds
{
	t_session	*t_status;
	char		*cmd_line;
	char		**cmd_splitted;
	t_token		**piped_cmd;
	t_token		*simple_cmd;
}	t_cmd_tab;

t_status	*init_shell(char *envp[]);
#endif
