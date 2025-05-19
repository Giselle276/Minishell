/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:03:54 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/05/19 12:54:37 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	build_argv(char **argv, t_token *arg)
{
	int	j;

	j = 0;
	while (arg && j < 255)
	{
		argv[j++] = ft_strdup(arg->value);
		arg = arg->next;
	}
	argv[j] = NULL;
}

void	exec_child(t_cmd *cmd, t_status *status)
{
	char	*argv[256];
	char	*path;

	handle_redirections(cmd);
	build_argv(argv, cmd->args);
	if (is_builtin(argv[0]))
	{
		status->stat = exec_builtin_cmd(argv, cmd, status);
		exit(status->error_code);
	}
	path = find_command_path(argv[0], status->envp);
	if (!path)
	{
		perror(argv[0]);
		exit(127);
	}
	execve(path, argv, status->envp);
	perror("execve");
	exit(127);
}
