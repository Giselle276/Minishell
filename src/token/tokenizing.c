/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:39:05 by claudia           #+#    #+#             */
/*   Updated: 2025/04/24 20:12:41 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// obtiene token por token revisando el estado de las comillas

static char *trim_quotes(char *token)
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

char *get_token(char *line, int *i)
{
	int		start;
	char	qt;
	char	*token;

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
		return (NULL);
	token = ft_substr(line, start, *i - start);
	if (!token)
		return (NULL);
	return (trim_quotes(token));
}

/*char	*get_token(char *line, int *i)
{
	int		start;
	char	qt;
	char	*token;
	char	*trimmed;
	
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
	token = ft_substr(line, start, *i - start);
	if (token[0] == '"' || token[0] == '\'')
	{
		trimmed = ft_substr(token, 1, ft_strlen(token) - 2);
		free(trimmed);
		printf("Antes de recortar: [%s] len: %zu\n", token, ft_strlen(token));
		printf("token[0]: %c  token[end]: %c\n", token[0], token[ft_strlen(token) - 1]);

		return (token);
	}
	return (token);
}*/

char	update_quote(char quote, char c) // solo cierra al ser iguales
{
	if ((c == '\'' || c == '\"') && quote == 0)
		return (c);
	else if (c == quote)
		return (0);
	return (quote);
}

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
