/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42madrid.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:43:11 by cgil              #+#    #+#             */
/*   Updated: 2024/09/25 11:06:37 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*last_ocurrence;
	unsigned char	ch;

	last_ocurrence = NULL;
	ch = (unsigned char)c;
	while (*s != '\0')
	{
		if (*s == ch)
		{
			last_ocurrence = (char *)s;
		}
		s++;
	}
	if (ch == '\0')
	{
		return ((char *)s);
	}
	return (last_ocurrence);
}
