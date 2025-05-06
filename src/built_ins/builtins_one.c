/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:39:39 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/05/06 16:27:50 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*int	builtin_cd(char **args, t_status *status)
{
	char	*home;

	home = get_env_value(status->envp, "HOME");
	if (!args[1] && home)
	{
		if (chdir(home) == 0)
			return (0);
		else
			return (1);
	}
	if (chdir(args[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}*/


static int	should_print_env_var(const char *env_var)
{
	char	*equal_sign;
	char	*value;

	equal_sign = ft_strchr(env_var, '=');
	if (!equal_sign)
		return (0);
	value = equal_sign + 1;
	if (value[0] == '\0')
		return (0);
	if (value[0] == '"' && value[1] == '"' && value[2] == '\0')
		return (0);
	return (1);
}

int	builtin_env(char **args, t_status *status)
{
	int	i;

	if (args[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		status->error_code = 127;
		return (127);
	}
	if (!status->envp || !status->envp[0])
	{
		write(2, "env: environment not set\n", 26);
		status->error_code = 1;
		return (1);
	}
	i = 0;
	while (status->envp[i])
	{
		if (should_print_env_var(status->envp[i]))
			printf("%s\n", status->envp[i]);
		i++;
	}
	status->error_code = 0;
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
int	builtin_exit(char **argv)
{
	int	code;

	code = 0;
	if (argv[1])
		code = ft_atoi(argv[1]);
	exit(code);
}