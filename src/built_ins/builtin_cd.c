/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:18:52 by claudia           #+#    #+#             */
/*   Updated: 2025/05/20 22:29:33 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*expand_path(char *arg, t_status *status)
{
	char	*home;
	char	*expanded;
	size_t	home_len;
	size_t	total_len;

	if (arg[0] != '~')
		return (ft_strdup(arg));
	home = get_env_value(status->envp, "HOME");
	if (!home)
		return (NULL);
	home_len = ft_strlen(home);
	total_len = home_len + ft_strlen(arg + 1) + 1;
	expanded = malloc(total_len);
	if (!expanded)
		return (NULL);
	ft_strcpy(expanded, home);
	ft_strlcat(expanded, arg + 1, total_len);
	return (expanded);
}

static int	change_dir(const char *path)
{
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

static void	update_pwd_vars(t_status *status, char *oldpwd)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		perror("getcwd");
		return ;
	}
	status->envp = set_env_value(status->envp, "OLDPWD", oldpwd);
	status->envp = set_env_value(status->envp, "PWD", newpwd);
	free(newpwd);
}

static char	*get_cd_target(char **args, t_status *status)
{
	char	*target;

	if (!args[1])
	{
		target = get_env_value(status->envp, "HOME");
		if (!target)
			return (write(2, "cd: HOME not set\n", 18), NULL);
		return (ft_strdup(target));
	}
	else if (strcmp(args[1], "-") == 0)
	{
		target = get_env_value(status->envp, "OLDPWD");
		if (!target)
			return (write(2, "cd: OLDPWD not set qe pasa\n", 18), NULL);
		printf("%s\n", target);
		return (ft_strdup(target));
	}
	else
		return (expand_path(args[1], status));
}

int	builtin_cd(char **args, t_status *status)
{
	char	*oldpwd;
	char	*target;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("getcwd"), 1);
	target = get_cd_target(args, status);
	if (!target)
	{
		if (!args[1])
			status->stat = 2;
		else
			status->stat = 1;
		free(oldpwd);
		return (status->stat);
	}
	if (change_dir(target) != 0)
		return (free(oldpwd), free(target), 1);
	update_pwd_vars(status, oldpwd);
	free(oldpwd);
	free(target);
	return (0);
}
