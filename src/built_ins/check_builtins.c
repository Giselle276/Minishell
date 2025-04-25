/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:58:53 by cgil              #+#    #+#             */
/*   Updated: 2025/04/23 19:19:52 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

bool	is_builtin(const char *cmd)
{
	if (!cmd)
		return (false);
	return (
		ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "export") == 0
	);
}

int	exec_builtin(char **argv, t_status *status)
{
	if (ft_strcmp(argv[0], "cd") == 0)
		return (builtin_cd(argv, status));
	else if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argv));
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argv));
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(argv[0], "env") == 0)
		return (builtin_env(argv, status));
	else if (ft_strcmp(argv[0], "export") == 0)
		return (builtin_export(argv, status));
	else if (ft_strcmp(argv[0], "unset") == 0)
		return (builtin_unset(argv, status));
	return (1);
}
