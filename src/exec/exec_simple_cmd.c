/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:51:58 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/04/19 16:59:33 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	fill_argv(char **argv, t_token *arg_token)
{
	int	i;

	i = 0;
	while (arg_token && i < 255)
	{
		argv[i++] = ft_strdup(arg_token->value);
		arg_token = arg_token->next;
	}
	argv[i] = NULL;
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

static void	exec_external_cmd(char **argv, t_cmd *cmd, t_status *status)
{
	pid_t	pid;
	int		code;

	pid = fork();
	if (pid == 0)
	{
		handle_redirections(cmd);
		execvp(argv[0], argv);
		perror("execvp");
		exit(127);
	}
	else if (pid > 0)
	{
		waitpid(pid, &code, 0);
		free_argv(argv);
		status->stat = WEXITSTATUS(code);
	}
	else
		perror("fork");
}

int	exec_simple_command(t_cmds *ct)
{
	t_cmd	*cmd;
	char	*argv[256];

	cmd = ct->parsed_simple;
	fill_argv(argv, cmd->args);
	if (!argv[0])
		return (0);
	if (is_builtin(argv[0]))
	{
		ct->status->stat = exec_builtin_cmd(argv, cmd, ct->status);
		return (ct->status->stat);
	}
	exec_external_cmd(argv, cmd, ct->status);
	return (0);
}
