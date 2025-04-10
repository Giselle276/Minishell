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
