/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:52:10 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/04/23 13:05:30 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	ignore_builtin_in_pipeline(const char *cmd)
{
	return (
		ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0
	);
}

void	build_argv(char **argv, t_token *arg)
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

void	setup_fds(t_cmd *cmd, int prev_fd, int *pipefd, int is_last)
{
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
}

void	exec_builtin_or_exit(char **argv)
{
	if (ignore_builtin_in_pipeline(argv[0]))
		exit(0);
	exec_builtin(argv, g_shell_status);
	exit(0);
}

void	exec_external(char **argv)
{
	char	*path;

	path = find_command_path(argv[0]);
	if (!path)
	{
		perror(argv[0]);
		exit(127);
	}
	execve(path, argv, g_shell_status->envp);
	perror("execve");
	exit(127);
}
