/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:48:30 by claudia           #+#    #+#             */
/*   Updated: 2025/05/02 12:20:19 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*char	*join_adjacent_quoted(char *line, int *i, char *quote_type)
{
	char	*result;
	char	*part;
	int		start;
	char	quote;
	char	*temp;

	result = NULL;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	while (line[*i] && line[*i] != ' ')
	{
		quote = 0;
		if (line[*i] == '"' || line[*i] == '\'')
		{
			quote = line[*i];
			if (*quote_type == 0)
				*quote_type = quote;
			(*i)++;
			start = *i;
			while (line[*i] && line[*i] != quote)
				(*i)++;
			if (!line[*i])
			{
				ft_putstr_fd("minishell: unclosed quote\n", 2);
				free(result);
				return (NULL);
			}
			part = ft_substr(line, start, *i - start);
			(*i)++;
		}
		else
		{
			start = *i;
			while (line[*i] && line[*i] != ' ' && line[*i] != '"' && line[*i] != '\'')
				(*i)++;
			part = ft_substr(line, start, *i - start);
		}
		if (!part)
			return (free(result), NULL);
		if (!result)
			result = part;
		else
		{
			temp = ft_strjoin(result, part);
			free(result);
			free(part);
			result = temp;
		}
	}
	return (result);
}*/

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





