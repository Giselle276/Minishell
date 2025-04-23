/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:57:22 by cgil              #+#    #+#             */
/*   Updated: 2025/04/23 14:01:38 by gmaccha-         ###   ########.fr       */
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

int	builtin_export(char **argv, t_status *status)
{
	int		i;
	char	*sep;
	char	*key;
	char	*value;

	if (!argv[1])
		return (builtin_env(status));
	i = 1;
	while (argv[i])
	{
		sep = ft_strchr(argv[i], '=');
		if (sep)
		{
			*sep = '\0';
			key = argv[i];
			value = sep + 1;
			status->envp = set_env_value(status->envp, key, value);
			*sep = '=';
		}
		else
			status->envp = set_env_value(status->envp, argv[i], "");
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
