/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:17:04 by claudia           #+#    #+#             */
/*   Updated: 2025/03/31 15:47:17 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_status	*init_shell(char *envp[]) // puntero de variables de entorno
{
	t_status	*status;

	status = (t_status *)malloc(sizeof(t_status));
	if (!status)
		error_exit(EALLOC);
	//status->env = load_env(envp); // to do
	status->envp = envp;
	status->error_code = 0;
	status->stat = 0;
	status->child_envp = NULL;
	//status->process_lst = NULL; // to do
	status->std_fd[0] = STDIN_FILENO;
	status->std_fd[1] = STDOUT_FILENO;
	return (status);
}

t_cmds	*init_cmds_table(t_status *shell_st)
{
	t_cmds	*cmds_table;

	cmds_table = (t_cmds *)malloc(sizeof(t_cmds));
	if (!cmds_table)
		error_exit(EALLOC);
	cmds_table->status = shell_st;
	cmds_table->cmd_line = NULL;
	cmds_table->cmd_splitted = NULL;
	//cmds_table->piped_cmd = NULL;
	//cmds_table->simple_cmd = NULL;
	return (cmds_table);
}
