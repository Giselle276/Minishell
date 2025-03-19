/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-18 11:56:42 by gmaccha-          #+#    #+#             */
/*   Updated: 2025-03-18 11:56:42 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*t_status	*init_shell(char *envp[])
{
	t_status	*shell_status;

	shell_status = ft_calloc(1, sizeof(t_session));

	if (!shell_status)
		print_error("Error Initializing Shell");
	shell_status->env = load_env(envp);
	shell_status->envp = envp;
	shell_status->errcd = 0;
	shell_status->stat = 0;
	shell_status->child_envp = NULL;
	shell_status->process_lst = NULL;
	shell_status->std_fd[0] = STDIN_FILENO;
	shell_status->std_fd[1] = STDOUT_FILENO;
	return (shell_status);
}*/
