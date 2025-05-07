/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:39:39 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/05/07 12:25:06 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

static int	is_numeric(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!isdigit((unsigned char)str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **argv)
{
	int	code;

	code = 0;
	printf("exit\n");
	if (argv[1])
	{
		if (!is_numeric(argv[1]))
		{
			write(2, "minshell: numeric argument required\n", 37);
			exit(2);
		}
		if (argv[2])
		{
			write(2, "minishell: too many arguments\n", 31);
			return (1);
		}
		code = ft_atoi(argv[1]);
	}
	exit(code);
}

