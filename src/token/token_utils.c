/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:12:45 by claudia           #+#    #+#             */
/*   Updated: 2025/04/15 11:13:03 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token_type	get_token_type(char *str)
{
	printf("DEBUG get_token_type: '%s'\n", str);
	if (!str)
		return (T_WORD);
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
//asigna memoria para el token
t_token *create_token(char *str)
{
	t_token *new = malloc(sizeof(t_token));

	if (!new)
		return (NULL);
	new->value = ft_strdup(str);
	new->type = get_token_type(str);
	new->next = NULL;
	return (new);
}
// agrega el token al final de la lista
void	add_token(t_token **tk_list, t_token * new_token)
{
	t_token *tmp;

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

void	free_tokens(t_token *list)
{
	t_token *tmp;

	while (list)
	{
		tmp = list->next;
		free(list->value);
		free(list);
		list = tmp;
	}
}