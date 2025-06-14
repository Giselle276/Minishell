/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:17:48 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/05/09 20:33:41 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_root(t_status *st, t_cmds *ct)
{
	if (ct->parsed_simple)
		exec_simple_command(ct, st);
	else if (ct->parsed_cmds)
		exec_pipeline(ct, st);
}

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
	return (token->type == T_WORD
		&& ft_strchr(token->value, '$')
		&& token->quote_type != '\'');
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
		if (is_expandable_token(tmp) && tmp->quote_type != '\'')
			expand_token_value(tmp, status);
		tmp = tmp->next;
	}
}
