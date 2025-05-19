/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:09:31 by claudia           #+#    #+#             */
/*   Updated: 2025/05/19 12:32:51 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	wait_for_children(int count, t_status *status)
{
	int	wstatus;

	while (count--)
	{
		wait(&wstatus);
		if (WIFSIGNALED(wstatus))
			status->stat = 128 + WTERMSIG(wstatus);
		else if (WIFEXITED(wstatus))
			status->stat = WEXITSTATUS(wstatus);
	}
}

static void	handle_child(t_cmd *cmd, int *prev_fd,
		int *pipefd, t_status *status)
{
	if (*prev_fd != -1)
	{
		dup2(*prev_fd, STDIN_FILENO);
		close(*prev_fd);
	}
	if (pipefd[1] != -1)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	exec_child(cmd, status);
}

static void	execute_one_command(t_cmd *cmd, int *prev_fd,
		t_status *status, int is_last)
{
	int		pipefd[2];
	pid_t	pid;

	if (!is_last)
		pipe(pipefd);
	else
	{
		pipefd[0] = -1;
		pipefd[1] = -1;
	}
	pid = fork();
	if (pid == 0)
		handle_child(cmd, prev_fd, pipefd, status);
	else
	{
		if (*prev_fd != -1)
			close(*prev_fd);
		if (!is_last)
		{
			close(pipefd[1]);
			*prev_fd = pipefd[0];
		}
		else
			*prev_fd = -1;
	}
}

static void	execute_pipeline_loop(t_cmd **cmds, t_status *status)
{
	int		i;
	int		prev_fd;
	int		is_last;

	i = 0;
	prev_fd = -1;
	while (cmds[i])
	{
		is_last = (cmds[i + 1] == NULL);
		execute_one_command(cmds[i], &prev_fd, status, is_last);
		i++;
	}
	wait_for_children(i, status);
}

int	exec_pipeline(t_cmds *ct, t_status *status)
{
	execute_pipeline_loop(ct->parsed_cmds, status);
	return (0);
}
