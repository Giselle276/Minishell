/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:17:04 by claudia           #+#    #+#             */
/*   Updated: 2025/04/30 19:00:09 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_status	*init_shell(char *envp[]) // puntero de variables de entorno
{
	t_status	*status;

	status = (t_status *)malloc(sizeof(t_status));
	if (!status)
		validate_error(EALLOC, "Error while allocating memory with malloc",
			NULL);
	status->envp = load_env(envp);
	status->error_code = 0;
	status->stat = 0;
	status->child_envp = NULL;
	/*status->std_fd[0] = STDIN_FILENO;
	status->std_fd[1] = STDOUT_FILENO;*/
	return (status);
}

t_cmds	*init_cmds_table(void)
{
	t_cmds	*cmds_table;

	cmds_table = (t_cmds *)malloc(sizeof(t_cmds));
	if (!cmds_table)
		validate_error(EALLOC, "Error while allocating memory with malloc",
			cmds_table);
	cmds_table->cmd_line = NULL;
	cmds_table->piped_cmd = NULL;
	cmds_table->not_piped_cmd = NULL;
	cmds_table->parsed_cmds = NULL;
	cmds_table->parsed_simple = NULL;
	return (cmds_table);
}
