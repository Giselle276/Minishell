/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:30:52 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/05/06 10:40:58 by gmaccha-         ###   ########.fr       */
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
				ft_putstr_fd("zsh: syntax error near unexpected token `newline'\n", 2);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
