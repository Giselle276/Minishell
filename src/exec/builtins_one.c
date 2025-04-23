/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:39:39 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/04/23 19:16:10 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_cd(char **args, t_status *status)
{
	char	*home;

	home = get_env_value(status->envp, "HOME");
	if (!args[1] && home)
		return (chdir(home));
	if (chdir(args[1]) != 0)
	{
		perror("cd");
		status->stat = 1;
		return (1);
	}
	return (0);
}

int	builtin_exit(char **argv)
{
	int	code;

	code = 0;
	if (argv[1])
		code = ft_atoi(argv[1]);
	exit(code);
}

int	builtin_env(char **args, t_status *status)
{
	int	i = 0;

	if (args[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("':No such file or directory\n", 2);
		g_shell_status->error_code = 127;
		return(127);
	}
	if (!status->envp || !status->envp[0])
	{
		write(2, "env: environment not set\n", 26);
		g_shell_status->error_code = 1;
		return (1);
	}
	while (status->envp[i])
	{
		if (ft_strchr(status->envp[i], '=')) // solo imprime si hay '='
			printf("%s\n", status->envp[i]);
		i++;
	}
	g_shell_status->error_code = 0;
	return (0);
}

char	**load_env(char **envp)
{
	char	**copy;
	int		count;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[count] = NULL;
	return (copy);
}
