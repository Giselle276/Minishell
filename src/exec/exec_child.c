/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:08:03 by cgil              #+#    #+#             */
/*   Updated: 2025/05/16 15:34:37 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*full;
	int		i;

	if (!cmd)
		return (NULL);
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

static void	handle_path_error(char *path, char **argv, int code)
{
	if (code == 127)
		validate_path(path, argv);
	else if (code == 126)
		error_denied(argv);
	free(path);
	free_argv(argv);
	exit(code);
}

static char	*validate_and_get_path(char **argv, t_status *status)
{
	char	*path;

	path = find_command_path(argv[0], status->envp);
	if (!path)
		handle_path_error(NULL, argv, 127);
	if (access(path, F_OK) != 0)
		handle_path_error(path, argv, 127);
	if (access(path, X_OK) != 0)
		handle_path_error(path, argv, 126);
	return (path);
}

void	exec_child_process(char **argv, t_cmd *cmd, t_status *status)
{
	char	*path;

	handle_redirections(cmd);
	path = validate_and_get_path(argv, status);
	execve(path, argv, status->envp);
	free(path);
	error_denied(argv);
	free_argv(argv);
	exit(127);
}
