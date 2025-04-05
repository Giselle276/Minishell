/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:51:43 by cgil              #+#    #+#             */
/*   Updated: 2025/04/05 17:04:55 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "./minishell.h"

/*typedef struct s_status
{
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
	//t_token	*token_lst;
	char		**cmd_splitted;
	//t_token	**piped_cmd;
	t_token		*not_piped_cmd;
}				t_cmds;*/

void		shell_loop(t_status *shell_status);
t_cmds		*init_cmds_table(t_status *shell_st);
t_status	*init_shell(char *envp[]);

///////////// prompt
void		process_prompt(t_cmds *ct);

//////////// signals
void		signal_c(int sg);
void		handle_signal_before(void);

// error
int		validate_error(t_errcode err_code, char *err, t_cmds *ct);
void	print_err(char *err, int err_code);

#endif
