/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:05:30 by claudia           #+#    #+#             */
/*   Updated: 2025/05/09 18:06:21 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_token	*if_redirection(t_cmd *cmd, t_token *tmp)
{
	t_token	*new;

	if (!tmp->next)
		return (tmp);
	new = malloc(sizeof(t_token));
	new->value = ft_strdup(tmp->next->value);
	new->type = tmp->type;
	new->next = NULL;
	if (tmp->type == T_REDIR_IN || tmp->type == T_HEREDOC)
		add_token(&cmd->redir_in, new);
	else if (tmp->type == T_REDIR_OUT || tmp->type == T_APPEND)
		add_token(&cmd->redir_out, new);
	return (tmp->next);
}

t_token	*handle_tokens(t_cmd *cmd, t_token *tmp)
{
	if (tmp->type == T_REDIR_IN || tmp->type == T_HEREDOC
		|| tmp->type == T_REDIR_OUT || tmp->type == T_APPEND)
		tmp = if_redirection(cmd, tmp);
	else if (tmp->type == T_WORD || tmp->type == T_BUILTIN)
		add_token(&cmd->args, create_token(tmp->value));
	return (tmp->next);
}
