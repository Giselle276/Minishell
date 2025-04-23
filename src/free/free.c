/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:21:22 by cgil              #+#    #+#             */
/*   Updated: 2025/04/23 12:29:44 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_shell(t_status *shell_st)
{
	if (!shell_st)
		return ;
	free_str_array(shell_st->child_envp);
	free_envp(shell_st->envp);
	free(shell_st);
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_tokens(cmd->args);
	free_tokens(cmd->redir_in);
	free_tokens(cmd->redir_out);
	free(cmd);
}

void	free_cmds_array(t_cmd **cmds)
{
	int	i;

	if (!cmds)
		return ;
	i = 0;
	while (cmds[i])
	{
		free_cmd(cmds[i]);
		i++;
	}
	free(cmds);
}

void	free_cmds_table(t_cmds *cmds_table)
{
	int	i;

	if (!cmds_table)
		return ;
	if (cmds_table->cmd_line)
		free(cmds_table->cmd_line);
	if (cmds_table->token_lst)
		free_tokens(cmds_table->token_lst);
	if (cmds_table->piped_cmd)
	{
		i = 0;
		while (cmds_table->piped_cmd[i])
		{
			free_tokens(cmds_table->piped_cmd[i]);
			i++;
		}
		free(cmds_table->piped_cmd);
	}
	if (cmds_table->not_piped_cmd)
		free_tokens(cmds_table->not_piped_cmd);
	if (cmds_table->parsed_cmds)
		free_cmds_array(cmds_table->parsed_cmds);
	if (cmds_table->parsed_simple)
		free_cmd(cmds_table->parsed_simple);
	free(cmds_table);
}
