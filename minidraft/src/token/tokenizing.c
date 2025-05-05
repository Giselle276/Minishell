/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:58:36 by cgil              #+#    #+#             */
/*   Updated: 2025/05/02 12:24:42 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*char	*get_token(char *line, int *i, char *quote_type)
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
		status->error_code = 2; // REVISAR
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
}*/

t_token	*create_and_validate_tk(char *tk_str, t_status *status)
{
	t_token	*new_token;

	new_token = create_token(tk_str);
	if (new_token->type == T_INVALID)
	{
		ft_putstr_fd("Minishell: syntax error\n", 2);
		status->error_code = 2; // REVISAR
		free(new_token->value);
		free(new_token);
		return (NULL);
	}
	return (new_token);
}

t_token	*create_and_add_token(char *cmd_line, int *i,
	t_status *status, t_token **tk_lst)
{
	char	*tk_str;
	char	quote_type;
	t_token	*new_token;

	quote_type = 0;
	tk_str = join_adjacent_quoted(cmd_line, i, &quote_type);
	if (!tk_str)
	{
		free_tokens(*tk_lst);
		return (NULL);
	}
	new_token = create_and_validate_tk(tk_str, status);
	if (!new_token)
	{
		free(tk_str);
		free_tokens(*tk_lst);
		return (NULL);
	}
	new_token->quote_type = quote_type;
	free(tk_str);
	add_token(tk_lst, new_token);
	return (new_token);
}


t_token	*process_tokens(char *cmd_line, t_status *status)
{
	t_token	*new_token;
	t_token	*tk_lst;
	int		i;

	tk_lst = NULL;
	i = 0;
	while (cmd_line[i])
	{
		new_token = create_and_add_token(cmd_line, &i, status, &tk_lst);
		if (!new_token)
			return (NULL);
	}
	return (tk_lst);
}

t_token	*tokenize_line(char *cmd_line, t_status *status)
{
	if (!cmd_line)
		return (NULL);
	return (process_tokens(cmd_line, status));
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
