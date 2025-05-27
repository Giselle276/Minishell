/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:17:04 by claudia           #+#    #+#             */
/*   Updated: 2025/05/27 12:12:35 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	export_env(char ***env, char *var, char *new_entry)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], var, 6) == 0)
		{
			(*env)[i] = new_entry;
			return ;
		}
		i++;
	}
	i = 0;
	while ((*env)[i])
		i++;
	(*env)[i] = new_entry;
	(*env)[i + 1] = NULL;
}

void	update_shlvl(char ***env)
{
	char	*lvl_str;
	int		lvl;
	char	*new_lvl;
	char	*new_entry;

	lvl_str = get_env_value(*env, "SHLVL");
	if (lvl_str)
		lvl = ft_atoi(lvl_str);
	else
		lvl = 0;
	lvl++;
	new_lvl = ft_itoa(lvl);
	new_entry = ft_strjoin("SHLVL=", new_lvl);
	free(new_lvl);
	export_env(env, "SHLVL=", new_entry);
}

t_status	*init_shell(char *envp[])
{
	t_status	*status;

	status = (t_status *)malloc(sizeof(t_status));
	if (!status)
		validate_error(EALLOC, "Error while allocating memory with malloc",
			NULL);
	update_shlvl(&envp);
	status->envp = load_env(envp);
	status->error_code = 0;
	status->stat = 0;
	return (status);
}

t_cmds	*init_cmds_table(void)
{
	t_cmds	*cmds_table;

	cmds_table = (t_cmds *)malloc(sizeof(t_cmds));
	if (!cmds_table)
		validate_error(EALLOC, "Error while allocating memory with malloc",
			cmds_table);
	cmds_table->cmd_line = NULL;
	cmds_table->piped_cmd = NULL;
	cmds_table->not_piped_cmd = NULL;
	cmds_table->parsed_cmds = NULL;
	cmds_table->parsed_simple = NULL;
	return (cmds_table);
}
