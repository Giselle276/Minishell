/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piped_tk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:13:27 by claudia           #+#    #+#             */
/*   Updated: 2025/04/15 11:17:18 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// obtiene token por token revisando el estado de las comillas
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

// devuelve un puntero a un array de listas de tokens
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
	current = NULL; // tokens de comando actual
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