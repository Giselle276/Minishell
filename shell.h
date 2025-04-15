/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:51:43 by cgil              #+#    #+#             */
/*   Updated: 2025/04/15 12:36:08 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "./minishell.h"

void		shell_loop(t_status *shell_status);
t_cmds		*init_cmds_table(t_status *shell_st);
t_status	*init_shell(char *envp[]);

///////////// prompt
void		process_prompt(t_cmds *ct);

//////////// signals
void		signal_c(int sg);
void		handle_signal_before(void);

// error
int			validate_error(t_errcode err_code, char *err, t_cmds *ct);
void		print_err(char *err, int err_code);

//parse

t_cmd *parse_cmd_tokens(t_token *tokens);
t_cmd **parse_all_cmds(t_token **piped_cmds);
void print_cmd(t_cmd *cmd);
void print_pipes_only(t_token *lst);
bool	is_valid_pipe_syntax(t_token *lst);

#endif
