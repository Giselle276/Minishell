/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:17:04 by claudia           #+#    #+#             */
/*   Updated: 2025/03/27 16:06:38 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_status *init_shell(char *envp[]) // puntero de variables de entorno
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
