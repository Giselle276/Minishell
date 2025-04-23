/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:39:39 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/04/23 13:51:12 by cgil             ###   ########.fr       */
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

static int	is_n_flag(const char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (i > 1);
}

int	builtin_echo(char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (argv[i] && is_n_flag(argv[i]))
	{
		newline = 0;
		i++;
	}

	while (argv[i])
	{
		write(1, argv[i], strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
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
/*
int	builtin_env(t_status *status)
{
	int	i;
  
	i = 0;
	printf(">> Entrando a builtin_env()\n");
	if (!status->envp || !status->envp[0])
	{
		write(2, "env: environment not set\n", 26);
		return (1);
	}
	while (status->envp[i])
	{
		if (ft_strchr(status->envp[i], '='))
			printf("%s\n", status->envp[i]);
		i++;
	}
	return (0);
}*/

int	handle_env_and_exec(char **args, t_status *status)
{
	char 	*new_env_var;
	
	if (strchr(args[1], '=')!= NULL)
	{
		new_env_var = args[1];
		//set_env_value(&(status->envp), new_env_var);
		if (args[2] != NULL)
		{
			exec_external_cmd(args + 2, NULL, status);
			return (0);
		}
	}
	else
	{
		write(2, "ENV: Incorrect use of arguments", 32);
		return (1);
	}
}

int	builtin_env(char **args,t_status *status)
{
	char	**env;
	
	if (args[1] == NULL) // sin argumentos
	{
		env = status->envp;
		while (*env)
		{
			printf("%s\n", *env);
			env++;
		}
		return (0);
	}
	return (handle_env_and_exec(args, status));
}
