/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:57:22 by cgil              #+#    #+#             */
/*   Updated: 2025/05/02 17:21:06 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	perror("pwd");
	return (1);
}
//perfecta pero muy larga
/*int	builtin_export(char **argv, t_status *status)
{
	int		i;
	char	*sep;
	char	*key;
	char	*value;	

	i = 1;
	if (!argv[1])
	{
		i = 0;
		while (status->envp[i])
		{
			printf("declare -x %s\n", status->envp[i]);
			i++;
		}
		return (0);
	}
	while (argv[i])
	{
		sep = ft_strchr(argv[i], '=');
		if (sep)
		{
			*sep = '\0';
			key = argv[i];
			value = sep + 1;
			status->envp = set_env_value(status->envp, key, value);
			*sep = '='; // Restaurar la cadena original
		}
		else
			status->envp = set_env_value(status->envp, argv[i], "");
		i++;
	}
	return (0);
}*/

void	print_exported_env(t_status *status)
{
	int	i;

	i = 0;
	while (status->envp[i])
	{
		printf("declare -x %s\n", status->envp[i]);
		i++;
	}
}

void	process_export_argument(char *arg, t_status *status)
{
	char	*sep;
	char	*key;
	char	*value;

	sep = ft_strchr(arg, '=');
	if (sep)
	{
		*sep = '\0';
		key = arg;
		value = sep + 1;
		if (value[0] == '\0')
			value = "\"\"";
		status->envp = set_env_value(status->envp, key, value);
		*sep = '=';
	}
	else
		status->envp = set_env_value(status->envp, arg, NULL);
}

int	builtin_export(char **argv, t_status *status)
{
	int	i;

	i = 1;
	if (!argv[1])
	{
		print_exported_env(status);
		return (0);
	}
	while (argv[i])
	{
		process_export_argument(argv[i], status);
		i++;
	}
	return (0);
}

int	builtin_unset(char **argv, t_status *status)
{
	int	i;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		status->envp = unset_env_value(status->envp, argv[i]);
		i++;
	}
	return (0);
}

