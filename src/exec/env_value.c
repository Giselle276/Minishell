/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:39:48 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/04/23 12:35:49 by gmaccha-         ###   ########.fr       */
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
/*
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
*/

static char	**append_env_var(char **envp, char *new_var, int len)
{
	char	**new_envp;
	int		i;

	i = 0;
	new_envp = malloc(sizeof(char *) * (len + 2));
	if (!new_envp)
		return (NULL);
	while (i < len)
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[i++] = new_var;
	new_envp[i] = NULL;
	free(envp);
	return (new_envp);
}

char	**set_env_value(char **envp, const char *name, const char *value)
{
	int		index;
	int		len;
	char	*new_var;

	new_var = ft_strjoin(name, "=");
	if (!new_var)
		return (NULL);
	new_var = ft_strjoin_free(new_var, value);
	if (!new_var)
		return (NULL);
	index = env_var_exists(envp, name);
	if (index >= 0)
	{
		free(envp[index]);
		envp[index] = new_var;
		return (envp);
	}
	len = env_len(envp);
	return (append_env_var(envp, new_var, len));
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
