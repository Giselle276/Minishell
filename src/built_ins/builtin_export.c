/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:42:06 by claudia           #+#    #+#             */
/*   Updated: 2025/05/20 21:45:18 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_exported_env(t_status *status)
{
	int		i;
	char	*sep;
	char	*key;
	char	*value;

	i = 0;
	while (status->envp[i])
	{
		sep = ft_strchr(status->envp[i], '=');
		if (sep)
		{
			*sep = '\0';
			key = status->envp[i];
			value = sep + 1;
			printf("declare -x %s=\"%s\"\n", key, value);
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

	if (!is_valid_identifier(arg))
	{
		write(2, "minishell: export: not a valid identifier\n", 43);
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
			value = "";
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

	status->error_code = 0;
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
	return (status->error_code);
}
