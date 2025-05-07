/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:30:52 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/05/07 13:36:16 by gmaccha-         ###   ########.fr       */
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
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
