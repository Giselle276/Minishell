/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:57:22 by cgil              #+#    #+#             */
/*   Updated: 2025/05/05 12:46:43 by cgil             ###   ########.fr       */
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

void	print_exported_env(t_status *status)
{
	int		i;
	char	*sep;

	i = 0;
	while (status->envp[i])
	{
		sep = ft_strchr(status->envp[i], '=');
		if (sep)
		{
			*sep = '\0';
			printf("declare -x %s=\"%s\"\n", status->envp[i], sep + 1);
			*sep = '=';
		}
		else
			printf("declare -x %s\n", status->envp[i]);
		i++;
	}
}

void	process_export_argument(char *arg, t_status *status)
{
	char	*sep;
	char	*key;
	char	*value;

	if(arg[0] == '\0')
	{
		write(2, "minishell: export: `': not a valid identifier\n", 47);
		status->error_code = 1;
		return ;
	}
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
		if (env_var_exists(status->envp, arg) == -1)
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

