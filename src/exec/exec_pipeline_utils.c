/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:09:31 by claudia           #+#    #+#             */
/*   Updated: 2025/05/16 16:13:20 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static pid_t	create_pipe_and_fork(int pipefd[2])
{
	pid_t	pid;

	if (pipe(pipefd) == -1)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	return (pid);
}

static void	execute_pipeline_loop(t_cmd **cmds, t_status *status)
{
	int		i;
	int		prev_fd;
	int		pipefd[2];
	pid_t	pid;
	int		wstatus;

	i = 0;
	prev_fd = -1;
	while (cmds[i])
	{
		pid = create_pipe_and_fork(pipefd);
		if (pid == 0)
			exec_child(cmds[i], prev_fd, pipefd, cmds[i + 1] == NULL, status);
		else
			handle_parent(&prev_fd, pipefd);
		i++;
	}
	while (i--)
	{
		wait(&wstatus);
		if (WIFSIGNALED(wstatus))
			status->stat = 128 + WTERMSIG(wstatus);
		else if (WIFEXITED(wstatus))
			status->stat = WEXITSTATUS(wstatus);
	}
}

int	exec_pipeline(t_cmds *ct, t_status *status)
{
	execute_pipeline_loop(ct->parsed_cmds, status);
	return (0);
}
