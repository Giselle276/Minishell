/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:39:48 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/04/19 20:29:35 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_env_value(char **envp, const char *name)
{
	int		i;
	size_t	len;

	if (!envp || !name)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

static int	env_var_exists(char **envp, const char *name)
{
	int		i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	**set_env_value(char **envp, const char *name, const char *value)
{
	int		i;
	char	**new_envp;
	char	*new_var;
	int		exists;

	new_var = ft_strjoin(name, "=");
	new_var = ft_strjoin_free(new_var, value);
	exists = env_var_exists(envp, name);
	if (exists >= 0)
	{
		free(envp[exists]);
		envp[exists] = new_var;
		return (envp);
	}
	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return (NULL);
	for (int j = 0; j < i; j++)
		new_envp[j] = envp[j];
	new_envp[i] = new_var;
	new_envp[i + 1] = NULL;
	free(envp);
	return (new_envp);
}

char	**unset_env_value(char **envp, const char *name)
{
	int		i;
	int		j;
	char	**new_envp;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(name);
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * i);
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			free(envp[i]);
		else
			new_envp[j++] = envp[i];
		i++;
	}
	new_envp[j] = NULL;
	free(envp);
	return (new_envp);
}
