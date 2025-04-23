/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_prueba.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:39:05 by claudia           #+#    #+#             */
/*   Updated: 2025/04/23 18:45:55 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// obtiene token por token revisando el estado de las comillas

char	*get_token(char *line, int *i)
{
	int		start;
	char	qt;

	start = 0;
	qt = 0;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	start = *i;
	while (line[*i])
	{
		qt = update_quote(qt, line[*i]);
		if (!qt && line[*i] == ' ')
			break ;
		(*i)++;
	}
	if (qt)
		return (NULL); // comillas no cerradas
	return (ft_substr(line, start, *i - start)); // retorna tokens cortados 
}

char	update_quote(char quote, char c) // solo cierra al ser iguales
{
	if ((c == '\'' || c == '\"') && quote == 0)
		return (c); // abre comilla
	else if (c == quote)
		return (0); // si es ' '
	return (quote);
}

// dirige a que se obtenga el token, se le asigne memoria y se incluya a la lista


t_token	*create_and_validate_tk(char *tk_str)
{
	t_token	*new_token;

	new_token = create_token(tk_str);
	if (new_token->type == T_INVALID)
	{
		ft_putstr_fd("Minishell: syntax error\n", 2);
		g_shell_status->error_code = 2;
		free(new_token->value);
		free(new_token);
		return (NULL);
	}
	return (new_token);
}

t_token	*tokenize_line(char *cmd_line)
{
	t_token	*tk_lst;
	t_token	*new_token;
	char	*tk_str;
	int		i;

	i = 0;
	tk_lst = NULL;
	while (cmd_line[i])
	{
		tk_str = get_token(cmd_line, &i);
		if (!tk_str)
		{
			free_tokens(tk_lst);
			return (NULL);
		}
		new_token = create_and_validate_tk(tk_str);
		free(tk_str);
		if (!new_token)
		{
			free_tokens(tk_lst);
			return (NULL);
		}
		add_token(&tk_lst, new_token);
	}
	return (tk_lst);
}

void	tokenizing(t_cmds *ct)
{
	ct->token_lst = tokenize_line(ct->cmd_line);
	if (!ct->token_lst)
		return ;
	if (!is_valid_pipe_syntax(ct->token_lst))
	{
		ft_putstr_fd("minishell: syntax error near pipe\n", 2);
		free_tokens(ct->token_lst);
		ct->token_lst = NULL;
		return ;
	}
}
