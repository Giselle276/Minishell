/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:03:54 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/04/19 18:20:48 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	build_argv(char **argv, t_token *arg)
{
	int	j;

	j = 0;
	while (arg && j < 255)
	{
		argv[j++] = arg->value;
		arg = arg->next;
	}
	argv[j] = NULL;
}

static void	execute_child(t_cmd *cmd, int prev_fd, int *pipefd, int is_last)
{
	t_token	*arg;
	char	*argv[256];

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
	arg = cmd->args;
	build_argv(argv, arg);
	execvp(argv[0], argv);
	perror("execvp");
	exit(127);
}

static void	handle_parent(int *prev_fd, int *pipefd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	close(pipefd[1]);
	*prev_fd = pipefd[0];
}

int	exec_pipeline(t_cmds *ct)
{
	int		i;
	int		pipefd[2];
	int		prev_fd;
	pid_t	pid;
	t_cmd	**cmds;

	i = 0;
	prev_fd = -1;
	cmds = ct->parsed_cmds;
	while (cmds[i])
	{
		if (pipe(pipefd) == -1)
			exit(1);
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
			execute_child(cmds[i], prev_fd, pipefd, cmds[i + 1] == NULL);
		else
			handle_parent(&prev_fd, pipefd);
		i++;
	}
	while (i--)
		wait(NULL);
	return (0);
}
