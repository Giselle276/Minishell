/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:03:06 by cgil              #+#    #+#             */
/*   Updated: 2025/05/05 16:50:07 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*concat_line(char **store, char *buffer);
char	*tidy_lines(char **store);
int		handle_errors(char **store, char *buffer, ssize_t bytes_read);
char	*ft_strdup_gnl(char *s);
char	*ft_strjoin_gnl(char *s1, char *s2);
size_t	ft_strlcpy_gnl(char *dest, char *src, size_t size);
char	*ft_strchr_gnl(char *s, int c);
size_t	ft_strlen_gnl(char *str);
#endif