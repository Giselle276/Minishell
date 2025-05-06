/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:12:45 by claudia           #+#    #+#             */
/*   Updated: 2025/05/06 09:49:53 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token_type	get_token_type(char *str)
{
	if (!str)
		return (T_INVALID);
	if (ft_strncmp(str, "||", 3) == 0)
		return (T_INVALID);
	if (ft_strncmp(str, "|", 2) == 0)
		return (T_PIPE);
	if (ft_strncmp(str, "<<", 3) == 0)
		return (T_HEREDOC);
	if (ft_strncmp(str, ">>", 3) == 0)
		return (T_APPEND);
	if (ft_strncmp(str, "<", 2) == 0)
		return (T_REDIR_IN);
	if (ft_strncmp(str, ">", 2) == 0)
		return (T_REDIR_OUT);
	return (T_WORD);
}

t_token	*create_token(char *str)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(str);
	new->type = get_token_type(str);
	new->next = NULL;
	return (new);
}

void	add_token(t_token **tk_list, t_token *new_token)
{
	t_token	*tmp;

	if (!*tk_list)
	{
		*tk_list = new_token;
		return ;
	}
	tmp = *tk_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->value);
		free(tmp);
	}
}

char	update_quote(char quote, char c)
{
	if ((c == '\'' || c == '\"') && quote == 0)
		return (c);
	else if (c == quote)
		return (0);
	return (quote);
}
