/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:03:54 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/04/30 16:07:00 by cgil             ###   ########.fr       */
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

static int	exec_builtin_cmd(char **argv, t_cmd *cmd, t_status *status)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;
	int	i;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	handle_redirections(cmd);
	ret = exec_builtin(argv, status);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	i = 0;
	while (argv[i])
		free(argv[i++]);
	return (ret);
}

static void	exec_child(t_cmd *cmd, int prev_fd,
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
		status->error_code = exec_builtin_cmd(argv, cmd, status);
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


static void	handle_parent(int *prev_fd, int *pipefd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	close(pipefd[1]);
	*prev_fd = pipefd[0];
}

int	exec_pipeline(t_cmds *ct, t_status *status)
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
			exec_child(cmds[i], prev_fd, pipefd, cmds[i + 1] == NULL, status);
		else
			handle_parent(&prev_fd, pipefd);
		i++;
	}
	while (i--)
		wait(NULL);
	return (0);
}
