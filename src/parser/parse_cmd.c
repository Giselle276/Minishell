/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:07:52 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/04/15 13:45:12 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*parse_cmd_tokens(t_token *tokens)
{
	t_cmd	*cmd;
	t_token	*tmp;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == T_REDIR_IN || tmp->type == T_HEREDOC)
		{
			if (tmp->next)
			{
				add_token(&cmd->redir_in, create_token(tmp->next->value));
				tmp = tmp->next;
			}
		}
		else if (tmp->type == T_REDIR_OUT || tmp->type == T_APPEND)
		{
			if (tmp->next)
			{
				add_token(&cmd->redir_out, create_token(tmp->next->value));
				tmp = tmp->next;
			}
		}
		else if (tmp->type == T_WORD || tmp->type == T_BUILTIN)
			add_token(&cmd->args, create_token(tmp->value));

		tmp = tmp->next;
	}
	return (cmd);
}


t_cmd	**parse_all_cmds(t_token **piped_cmds)
{
	int		i;
	t_cmd	**cmd_array;
	int		count;

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
