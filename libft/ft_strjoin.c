/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42madrid.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:01:38 by cgil              #+#    #+#             */
/*   Updated: 2024/09/27 15:36:21 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjoined;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	strjoined = (char *)malloc(len1 + len2 + 1);
	if (!strjoined)
		return (NULL);
	ft_strlcpy(strjoined, s1, len1 + 1);
	ft_strlcpy(strjoined + len1, s2, len2 + 1);
	return (strjoined);
}
