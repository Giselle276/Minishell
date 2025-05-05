/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:02:46 by cgil              #+#    #+#             */
/*   Updated: 2025/05/05 17:11:49 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*concat_line(char **store, char *buffer)
{
	char	*temp;

	temp = ft_strjoin_gnl(*store, buffer);
	free (*store);
	return (temp);
}

int	handle_errors(char **store, char *buffer, ssize_t bytes_read)
{
	if (bytes_read < 0 || (bytes_read == 0
			&& (*store == NULL || **store == 0)))
	{
		free(buffer);
		free(*store);
		*store = NULL;
		return (1);
	}
	return (0);
}

char	*tidy_lines(char **store)
{
	char	*new_line;
	size_t	line_len;
	char	*line;
	char	*new_store;

	new_line = ft_strchr_gnl(*store, '\n');
	if (new_line)
		line_len = (new_line - *store) + 1;
	else
		line_len = ft_strlen_gnl(*store);
	line = (char *)malloc (line_len + 1);
	ft_strlcpy_gnl(line, *store, line_len + 1);
	if (new_line)
	{
		new_store = ft_strdup_gnl(new_line + 1);
		free(*store);
		*store = new_store;
	}
	else
	{
		free(*store);
		*store = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*store = NULL;
	char		*buffer;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof (char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (store == NULL)
			store = ft_strdup_gnl(buffer);
		else
			store = concat_line(&store, buffer);
		if (ft_strchr_gnl(store, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (handle_errors(&store, buffer, bytes_read))
		return (NULL);
	free(buffer);
	return (tidy_lines(&store));
}
