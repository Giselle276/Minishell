/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:17:48 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/04/30 12:48:23 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		free(split[i++]);
	free(split);
}

static int	is_expandable_token(t_token *token)
{
	return (token->type == T_WORD &&
			ft_strchr(token->value, '$') &&
			token->quote_type != '\''); // no expandir si es comilla simple
}

static void	expand_token_value(t_token *token, t_status *status)
{
	char	*expanded;

	expanded = expand_var(token->value, status);
	free(token->value);
	token->value = expanded;
}

void	expand_env_vars(t_token *tokens, t_status *status)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (is_expandable_token(tmp))
			expand_token_value(tmp, status);
		tmp = tmp->next;
	}
}
