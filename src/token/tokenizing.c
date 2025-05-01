/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:58:36 by cgil              #+#    #+#             */
/*   Updated: 2025/04/30 15:59:59 by cgil             ###   ########.fr       */
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

char	*get_token(char *line, int *i, char *quote_type)
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
		return (ft_putstr_fd("Minishell: unclosed quote\n", 2), NULL);
	token = ft_substr(line, start, *i - start);
	if (!token)
		return (NULL);
	if (token[0] == '\'' || token[0] == '"')
		*quote_type = token[0];
	else
		*quote_type = 0;
	return (token);
}

t_token	*create_and_validate_tk(char *tk_str, t_status *status)
{
	t_token	*new_token;

	new_token = create_token(tk_str);
	if (new_token->type == T_INVALID)
	{
		ft_putstr_fd("Minishell: syntax error\n", 2);
		status->error_code = 2;
		free(new_token->value);
		free(new_token);
		return (NULL);
	}
	return (new_token);
}

t_token	*tokenize_line(char *cmd_line, t_status *status)
{
	t_token	*tk_lst;
	t_token	*new_token;
	char	*tk_str;
	int		i;
	char	quote_type;

	if (!cmd_line)
		return (NULL);
	i = 0;
	tk_lst = NULL;
	while (cmd_line[i])
	{
		tk_str = get_token(cmd_line, &i, &quote_type);
		if (!tk_str)
		{
			free_tokens(tk_lst);
			return (NULL);
		}
		new_token = create_and_validate_tk(tk_str, status);
		if (!new_token)
		{
			free(tk_str);
			free_tokens(tk_lst);
			return (NULL);
		}
		new_token->quote_type = quote_type;
		free(tk_str);
		add_token(&tk_lst, new_token);
	}
	return (tk_lst);
}

void	tokenizing(t_cmds *ct, t_status *status)
{
	ct->token_lst = tokenize_line(ct->cmd_line, status);
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
