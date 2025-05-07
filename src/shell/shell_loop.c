/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:28:05 by claudia           #+#    #+#             */
/*   Updated: 2025/05/07 11:11:07 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	remove_outer_quotes(t_token *token)
{
	size_t	len;
	char	*trimmed;

	if (!token || !token->value || token->type != T_WORD)
		return ;
	len = ft_strlen(token->value);
	if ((token->quote_type == '\'' || token->quote_type == '"')
		&& len >= 2 && token->value[0] == token->quote_type
		&& token->value[len - 1] == token->quote_type)
	{
		trimmed = ft_substr(token->value, 1, len - 2);
		if (!trimmed)
			return ;
		free(token->value);
		token->value = trimmed;
	}
}

static void	clean_quotes(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		remove_outer_quotes(tmp);
		tmp = tmp->next;
	}
}

void	shell_loop(t_status *status)
{
	t_cmds	*cmds_table;

	while (1)
	{
		cmds_table = init_cmds_table();
		process_prompt(cmds_table, status);
		if (status->error_code == 0)
			tokenizing(cmds_table, status);
		if (status->error_code == 0)
			expand_env_vars(cmds_table->token_lst, status);
		if (status->error_code == 0)
			clean_quotes(cmds_table->token_lst);
		if (status->error_code == 0)
		{
			parser(cmds_table);
			execute_root(status, cmds_table);
		}
		free_cmds_table(cmds_table);
	}
}
