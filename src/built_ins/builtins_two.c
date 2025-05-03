/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:57:22 by cgil              #+#    #+#             */
/*   Updated: 2025/05/01 19:33:46 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	builtin_pwd(void)
{
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	perror("pwd");
	return (1);
}

static int	is_valid_identifier(const char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

int	builtin_export(char **argv, t_status *status)
{
	int		i;
	char	*sep;
	char	*key;
	char	*value;

	if (!argv[1])
		return (builtin_env(argv, status));

	i = 1;
	while (argv[i])
	{
		sep = ft_strchr(argv[i], '=');
		if (sep)
		{
			*sep = '\0';
			key = argv[i];
			value = sep + 1;
			if (!is_valid_identifier(key))
			{
				ft_putstr_fd("zsh: export: `", 2);
				ft_putstr_fd(argv[i], 2);
				ft_putstr_fd("=", 2);
        		ft_putstr_fd(value, 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
			}
			else
				status->envp = set_env_value(status->envp, key, value);
			*sep = '=';
		}
		else
		{
			if (!is_valid_identifier(argv[i]))
			{
				ft_putstr_fd("export: `", 2);
				ft_putstr_fd(argv[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
			}
			else
				status->envp = set_env_value(status->envp, argv[i], "");
		}
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

