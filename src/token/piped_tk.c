/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped_tk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:13:27 by claudia           #+#    #+#             */
/*   Updated: 2025/05/16 15:27:29 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*trim_quotes(char *token)
{
	char	quote;
	char	*trimmed;
	size_t	len;

	if ((token[0] == '"' || token[0] == '\'') && ft_strlen(token) >= 2)
	{
		len = ft_strlen(token);
		quote = token[0];
		if (token[len - 1] == quote)
		{
			trimmed = ft_substr(token, 1, len - 2);
			free(token);
			return (trimmed);
		}
	}
	return (token);
}

bool	has_pipe(t_token *lst)
{
	while (lst)
	{
		if (lst->type == T_PIPE)
			return (true);
		lst = lst->next;
	}
	return (false);
}

int	count_pipes(t_token *lst)
{
	int	count;

	count = 1;
	while (lst)
	{
		if (lst->type == T_PIPE)
			count++;
		lst = lst->next;
	}
	return (count);
}

static void	add_token_to_current(t_token **current, t_token *token)
{
	t_token	*new;

	new = create_token(token->value);
	add_token(current, new);
}

t_token	**group_piped_cmd(t_token *token_lst)
{
	int		i;
	int		cmd_count;
	t_token	**piped_cmds;
	t_token	*current;

	i = 0;
	cmd_count = count_pipes(token_lst);
	piped_cmds = malloc(sizeof(t_token *) * (cmd_count + 1));
	current = NULL;
	if (!piped_cmds)
		return (NULL);
	while (token_lst)
	{
		if (token_lst->type == T_PIPE)
		{
			piped_cmds[i++] = current;
			current = NULL;
		}
		else
			add_token_to_current(&current, token_lst);
		token_lst = token_lst->next;
	}
	piped_cmds[i++] = current;
	piped_cmds[i] = NULL;
	return (piped_cmds);
}
