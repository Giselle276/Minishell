/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:51:43 by cgil              #+#    #+#             */
/*   Updated: 2025/03/24 18:54:34 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
#define SHELL_H

#include "minishell.h"

typedef struct s_status
{
	//t_hash_tab	*env;
	//t_process	*process_lst;
	char		**envp;
	char		**child_envp;
	int			error_code;
	int			stat;
	int			std_fd[2];
}				t_status;

typedef struct s_cmds
{
	t_status	*status;
	char		*cmd_line;
	char		**cmd_splitted;
	t_token		**piped_cmd;
	t_token		*simple_cmd;
}				t_cmds;

//t_status	*init_shell(char *envp[]);
void 		shell_loop(t_status *shell_status);
t_cmds  	*init_cmds_table(t_status *shell_st);
t_status 	*start_shell(char *envp);
///////////// prompt
void		process_prompt(t_cmds *ct);
//////////// signals
void		signal_c(int sg);
void	handle_signal_before(void);
#endif
