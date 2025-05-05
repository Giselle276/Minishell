/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:07:52 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/05/05 13:19:31 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// revisa si hay redirecciones y segun ellas crea y guarda
// el token de a donde se va realizar la redireccion
// si es un builtin lo guarda en args

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
			t_token *new = malloc(sizeof(t_token));
			new->value = ft_strdup(tmp->next->value);
			new->type = tmp->type;  // ✅ CONSERVA EL TIPO
			new->next = NULL;
			add_token(&cmd->redir_in, new);
			tmp = tmp->next;
		}
	}
	else if (tmp->type == T_REDIR_OUT || tmp->type == T_APPEND)
	{
		if (tmp->next)
		{
			t_token *new = malloc(sizeof(t_token));
			new->value = ft_strdup(tmp->next->value);
			new->type = tmp->type;  // ✅ CONSERVA EL TIPO
			new->next = NULL;
			add_token(&cmd->redir_out, new);
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
		//print_all_parsed_cmds(ct->parsed_cmds);
	}
	else
	{
		ct->parsed_simple = parse_cmd_tokens(ct->token_lst);
		//print_cmd(ct->parsed_simple);
	}
}
