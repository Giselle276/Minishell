/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:51:43 by cgil              #+#    #+#             */
/*   Updated: 2025/05/07 13:15:01 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "./minishell.h"

void		shell_loop(t_status *status);
t_cmds		*init_cmds_table(void);
t_status	*init_shell(char *envp[]);

///////////// prompt
void		process_prompt(t_cmds *ct, t_status *status);

//////////// signals
void		signal_c(int sg);
void		handle_signal_before(void);

// error
int			validate_error(t_errcode err_code, char *err, t_cmds *ct);
void		print_err(char *err, int err_code);
void		validate_path(char	*path, char **argv);
void		error_denied(char **argv);

//parse

t_cmd		*parse_cmd_tokens(t_token *tokens);
t_cmd		**parse_all_cmds(t_token **piped_cmds);
void		print_cmd(t_cmd *cmd);
void		print_pipes_only(t_token *lst);
bool		is_valid_pipe_syntax(t_token *lst);


///exec//////////////////////////////////////////////////////

void		execute_root(t_status *st, t_cmds *ct);
int			exec_simple_command(t_cmds *ct, t_status *status);
int			exec_pipeline(t_cmds *ct, t_status *status);
void		handle_redirections(t_cmd *cmd);
bool		is_builtin(const char *cmd);
int			exec_builtin(char **argv, t_status *status);
char		*trim_quotes(char *token);

//free
void		free_cmds_table(t_cmds *cmds_table);
void		free_tokens(t_token *head);
void		free_cmd(t_cmd *cmd);
void		free_cmds_array(t_cmd **cmds);
void		free_shell(t_status *shell_st);
void		free_str_array(char **arr);
void		free_envp(char **envp);
void		free_argv(char **argv);
void		free_split(char **split);

//built-in
int			builtin_cd(char **argvs, t_status *status);
int			builtin_echo(char **argv, t_status *status);
int			builtin_exit(char **argv);
int			builtin_pwd(void);
int			builtin_env(char **args, t_status *t_status);
char		**load_env(char **envp);
int			builtin_export(char **argv, t_status *status);
int			builtin_unset(char **argv, t_status *status);
int			exec_builtin_cmd(char **argv, t_cmd *cmd, t_status *status);

// get, set unset env value
char		*get_env_value(char **envp, const char *name);
char		**set_env_value(char **envp, const char *name, const char *value);
char		**unset_env_value(char **envp, const char *name);
char		*find_command_path(char *cmd, char **envp);
void		expand_env_vars(t_token *tokens, t_status *status);
char		*expand_var(const char *str, t_status *status);

//expand
int			is_assignment(char *str);
void		handle_assignment(char *assignment, t_status *status);
void		exec_external_cmd(char **argv, t_cmd *cmd, t_status *status);
void		exec_child_process(char **argv, t_cmd *cmd, t_status *status);
int			env_var_exists(char **envp, const char *name);

#endif