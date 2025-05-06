/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:48:30 by claudia           #+#    #+#             */
/*   Updated: 2025/05/06 09:48:28 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*process_quoted_token(char *line, int *i, char quote, char *quote_type)
{
	char	*token;
	int		start;

	if (*quote_type == 0)
		*quote_type = quote;
	start = *i + 1;
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
	{
		ft_putstr_fd("minishell: unclosed quote\n", 2);
		return (NULL);
	}
	token = ft_substr(line, start, *i - start);
	(*i)++;
	return (token);
}

char	*process_non_quoted_token(char *line, int *i)
{
	int	start;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '"' && line[*i] != '\'')
		(*i)++;
	return (ft_substr(line, start, *i - start));
}

static char	*join_tokens(char *result, char *part)
{
	char	*temp;

	if (!result)
		return (part);
	temp = ft_strjoin(result, part);
	free(result);
	free(part);
	return (temp);
}

char	*join_adjacent_quoted(char *line, int *i, char *quote_type)
{
	char	*result;
	char	*part;

	result = NULL;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	while (line[*i] && line[*i] != ' ')
	{
		part = NULL;
		if (line[*i] == '"' || line[*i] == '\'')
			part = process_quoted_token(line, i, line[*i], quote_type);
		else
			part = process_non_quoted_token(line, i);
		if (!part)
			return (free(result), NULL);
		result = join_tokens(result, part);
		if (!result)
			return (NULL);
	}
	return (result);
}





