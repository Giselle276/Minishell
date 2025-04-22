/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42madrid.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:10:10 by cgil              #+#    #+#             */
/*   Updated: 2024/10/09 11:59:20 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_counter(char const *s, char delimiter)
{
	int	i;
	int	word_index;
	int	in_word;

	i = 0;
	word_index = 0;
	in_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != delimiter && in_word == 0)
		{
			in_word = 1;
			word_index++;
		}
		else if (s[i] == delimiter)
			in_word = 0;
		i++;
	}
	return (word_index);
}

static char	**free_matrix(int position, char **matrix)
{
	while (position >= 0)
	{
		free(matrix[position--]);
	}
	free(matrix);
	return (NULL);
}

static char	**fill_matrix(const char *s, char delimiter, char **matrix)
{
	int	i;
	int	start;
	int	position;

	i = 0;
	position = 0;
	while (s[i] != '\0')
	{
		while (s[i] == delimiter)
			i++;
		start = i;
		while (s[i] != delimiter && s[i] != '\0')
		{
			i++;
			if (s[i] == delimiter || s[i] == '\0')
			{
				matrix[position] = ft_substr(s, start, i - start);
				if (!matrix[position])
					return (free_matrix(position, matrix));
				position++;
			}
		}
	}
	return (matrix);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**matrix;

	words = word_counter(s, c);
	matrix = (char **)ft_calloc((words + 1), sizeof(char *));
	if (!matrix)
		return (NULL);
	return (fill_matrix(s, c, matrix));
}
