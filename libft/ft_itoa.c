/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42madrid.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:07:17 by cgil              #+#    #+#             */
/*   Updated: 2024/10/10 14:38:38 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(int n)
{
	int	length;

	if (n <= 0)
		length = 1;
	else
	{
		length = 0;
	}
	while (n != 0)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

static void	convert_to_str(char *str, long num, int length)
{
	str[length] = '\0';
	if (num == 0)
	{
		str[0] = '0';
	}
	else
	{
		while (num > 0)
		{
			str[--length] = num % 10 + '0';
			num = num / 10;
		}
	}
}

char	*ft_itoa(int n)
{
	int		length;
	char	*str;
	long	num;

	length = num_len(n);
	str = malloc(length + 1);
	num = n;
	if (!str)
		return (0);
	if (num < 0)
	{
		str[0] = '-';
		num = num * -1;
	}
	convert_to_str(str, num, length);
	return (str);
}
