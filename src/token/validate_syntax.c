/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:30:52 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/05/19 17:01:30 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_redirection(t_token_type type)
{
	return (type == T_REDIR_OUT || type == T_APPEND
		|| type == T_REDIR_IN || type == T_HEREDOC);
}

int	is_valid_redirection_syntax(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (is_redirection(tmp->type))
		{
			if (!tmp->next || tmp->next->type != T_WORD)
			{
				ft_putstr_fd("minishell: syntax error near", 2);
				ft_putstr_fd("token `newline'\n", 2);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

bool	is_invalid_pipe_sequence(t_token *prev)
{
	return (!prev || prev->type == T_PIPE);
}

bool	is_invalid_next_token(t_token *lst)
{
	return (!lst->next
		|| lst->next->type == T_PIPE
		|| lst->next->type == T_HEREDOC);
}

bool	is_valid_pipe_syntax(t_token *lst)
{
	t_token	*prev;

	prev = NULL;
	if (!lst)
		return (true);
	while (lst)
	{
		if (lst->type == T_PIPE)
		{
			if (is_invalid_pipe_sequence(prev)
				|| is_invalid_next_token(lst))
			{
				ft_putstr_fd("minishell: syntax error near ", 2);
				ft_putstr_fd("unexpected token `|'\n", 2);
				return (false);
			}
		}
		prev = lst;
		lst = lst->next;
	}
	return (true);
}
