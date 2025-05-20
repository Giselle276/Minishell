/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:43:22 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/05/16 15:44:44 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_assignment(char *str)
{
	return (str && ft_strchr(str, '=') && str[0] != '=');
}

void	handle_assignment(char *assignment, t_status *status)
{
	char	*equal_pos;
	char	*name;
	char	*raw_value;
	char	*value;

	equal_pos = ft_strchr(assignment, '=');
	name = ft_substr(assignment, 0, equal_pos - assignment);
	raw_value = ft_strdup(equal_pos + 1);
	value = trim_quotes(raw_value);
	status->envp = set_env_value(status->envp, name, value);
	free(name);
	free(value);
}

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
		signal(SIGQUIT, SIG_DFL);
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
