/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:43:22 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/05/28 13:47:13 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	exec_parent_process(pid_t pid, char **argv, t_status *status)
{
	int	code;
	int	sig;

	waitpid(pid, &code, 0);
	free_argv(argv);
	if (WIFSIGNALED(code))
	{
		sig = WTERMSIG(code);
		status->stat = 128 + sig;
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
	}
	else if (WIFEXITED(code))
		status->stat = WEXITSTATUS(code);
}

void	exec_external_cmd(char **argv, t_cmd *cmd, t_status *status)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		exec_child_process(argv, cmd, status);
	}
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		exec_parent_process(pid, argv, status);
		signal(SIGINT, signal_c);
	}
	else
		perror("fork");
}
