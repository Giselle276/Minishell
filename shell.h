/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:51:43 by cgil              #+#    #+#             */
/*   Updated: 2025/04/17 17:21:23 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "./minishell.h"

extern t_status	*g_shell_status;

void		shell_loop(void);
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

t_cmd		*parse_cmd_tokens(t_token *tokens);
t_cmd		**parse_all_cmds(t_token **piped_cmds);
void		print_cmd(t_cmd *cmd);
void		print_pipes_only(t_token *lst);
bool		is_valid_pipe_syntax(t_token *lst);
void		execute_root(t_status *st, t_cmds *ct);
int         exec_simple_command(t_cmds *ct);
int         exec_pipeline(t_cmds *ct);
void        handle_redirections(t_cmd *cmd);
bool        is_builtin(const char *cmd);
int         exec_builtin(char **argv, t_status *status);

//free
void		free_cmds_table(t_cmds *cmds_table);
void		free_tokens(t_token *head);
void		free_cmd(t_cmd *cmd);
void		free_cmds_array(t_cmd **cmds);
void		free_shell(t_status *shell_st);
void		free_str_array(char **arr);
void		free_envp(char **envp);
void	    free_argv(char **argv);

//built-in
int			builtin_cd(char **argv, t_status *status);
int			builtin_echo(char **argv);
int			builtin_exit(char **argv);
int			builtin_pwd(void);
int			builtin_env(char **envp);
char		**load_env(char **envp);

#endif
