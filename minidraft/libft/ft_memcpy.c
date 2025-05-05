/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42madrid.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:18:57 by cgil              #+#    #+#             */
/*   Updated: 2024/10/08 15:09:53 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*source;
	size_t			i;

	d = (unsigned char *)dest;
	source = (unsigned char *)src;
	if (!d && !source)
		return (dest);
	i = 0;
	while (i < n)
	{
		d[i] = source[i];
		i++;
	}
	return (dest);
}
