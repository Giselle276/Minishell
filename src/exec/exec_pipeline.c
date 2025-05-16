/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:03:54 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/05/16 16:37:56 by claudia          ###   ########.fr       */
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

void	exec_child(t_cmd *cmd, int prev_fd,
	int *pipefd, int is_last, t_status *status)
{
	char	*argv[256];
	char	*path;

	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	handle_redirections(cmd);
	if (!is_last && cmd->redir_out == NULL)
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
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

void	handle_parent(int *prev_fd, int *pipefd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	close(pipefd[1]);
	*prev_fd = pipefd[0];
}