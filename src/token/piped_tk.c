/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped_tk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:13:27 by claudia           #+#    #+#             */
/*   Updated: 2025/05/09 18:19:35 by claudia          ###   ########.fr       */
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

t_token	**group_piped_cmd(t_token *token_lst)
{
	int		i;
	int		cmd_count;
	t_token	**piped_cmds;
	t_token	*current;
	t_token	*new;

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
		{
			new = create_token(token_lst->value);
			add_token(&current, new);
		}
		token_lst = token_lst->next;
	}
	piped_cmds[i++] = current;
	piped_cmds[i] = NULL;
	return (piped_cmds);
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
			if (!prev || prev->type == T_PIPE)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
				return (false);
			}
			if (!lst->next || lst->next->type == T_PIPE || lst->next->type == T_REDIR_IN || lst->next->type == T_REDIR_OUT || lst->next->type == T_APPEND || lst->next->type == T_HEREDOC)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
				return (false);
			}
		}
		prev = lst;
		lst = lst->next;
	}
	return (true);
}
