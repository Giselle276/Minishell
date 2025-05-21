/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:07:52 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/05/21 13:02:32 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
}

t_cmd	*parse_cmd_tokens(t_token *tokens)
{
	t_cmd	*cmd;
	t_token	*tmp;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	init_cmd(cmd);
	tmp = tokens;
	while (tmp)
	{
		tmp = handle_tokens(cmd, tmp);
	}
	return (cmd);
}

t_cmd	**parse_all_cmds(t_token **piped_cmds)
{
	int		i;
	int		count;
	t_cmd	**cmd_array;

	i = 0;
	while (piped_cmds[i])
		i++;
	count = i;
	cmd_array = malloc(sizeof(t_cmd *) * (count + 1));
	if (!cmd_array)
		return (NULL);
	i = 0;
	while (piped_cmds[i])
	{
		cmd_array[i] = parse_cmd_tokens(piped_cmds[i]);
		i++;
	}
	cmd_array[i] = NULL;
	return (cmd_array);
}

void	parser(t_cmds *ct)
{
	if (!ct->token_lst)
		return ;
	if (has_pipe(ct->token_lst))
	{
		ct->piped_cmd = group_piped_cmd(ct->token_lst);
		ct->parsed_cmds = parse_all_cmds(ct->piped_cmd);
	}
	else
	{
		ct->parsed_simple = parse_cmd_tokens(ct->token_lst);
	}
}
