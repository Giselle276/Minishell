/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:51:58 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/05/05 11:35:13 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*full;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = get_env_value(envp, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full = ft_strjoin(paths[i], "/");
		full = ft_strjoin_free(full, cmd);
		if (access(full, X_OK) == 0)
			return (free_split(paths), full);
		free(full);
	}
	return (free_split(paths), NULL);
}

static void	fill_argv(char **argv, t_token *arg_token)
{
	int	i;

	i = 0;
	while (arg_token && i < 255)
	{
		argv[i] = ft_strdup(arg_token->value);
		if (!argv[i])
		{
			while (i > 0)
				free(argv[--i]);
			return ;
		}
		arg_token = arg_token->next;
		i++;
	}
	argv[i] = NULL;
}

int	exec_builtin_cmd(char **argv, t_cmd *cmd, t_status *status)
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

void	exec_child_process(char **argv, t_cmd *cmd, t_status *status)
{
	char	*path;

	handle_redirections(cmd);
	path = find_command_path(argv[0], status->envp);
	if (!path)
	{
		validate_path(path, &argv[0]);
		free_argv(argv);
		exit(127);
	}
	if (access(path, F_OK) != 0)
	{
		free(path);
		ft_putstr_fd("zsh: no such file or directory: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd("\n", 2);
		free_argv(argv);
		exit(127);
	}
	else if (access(path, X_OK) != 0)
	{
		free(path);
		error_denied(argv);
		free_argv(argv);
		exit(126);
	}
	execve(path, argv, status->envp);
	free(path);
	error_denied(argv);
	free_argv(argv);
	exit(127);
}

int	exec_simple_command(t_cmds *ct, t_status *status)
{
	t_cmd	*cmd;
	char	*argv[256];

	cmd = ct->parsed_simple;
	fill_argv(argv, cmd->args);
	if (!argv[0] || ft_strlen(argv[0]) == 0)
	{
		free_argv(argv);
		return (0);
	}
	if (is_assignment(argv[0]))
	{
		handle_assignment(argv[0], status);
		free_argv(argv);
		return (0);
	}
	if (is_builtin(argv[0]))
	{
		status->stat = exec_builtin_cmd(argv, cmd, status);
		return (status->stat);
	}
	exec_external_cmd(argv, cmd, status);
	return (0);
}

