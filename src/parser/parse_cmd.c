/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:07:52 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/04/15 17:59:48 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// revisa si hay redirecciones y segun ellas crea y guarda
// el token de a donde se va realizar la redireccion
// si es un builtin lo guarda en args

/*t_cmd	*parse_cmd_tokens(t_token *tokens)
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
}*/

void	init_cmd(t_cmd *cmd)
{
	cmd->args = NULL;
	cmd->redir_in = NULL;
	cmd->redir_out = NULL;
}

t_token	*handle_tokens(t_cmd *cmd, t_token *tmp)
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
	return (tmp->next);
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

// 
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
