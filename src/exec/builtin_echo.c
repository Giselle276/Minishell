/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:38:51 by cgil              #+#    #+#             */
/*   Updated: 2025/04/23 18:39:06 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

static int	is_n_flag(const char *str)
{
	int i;

	if (!str || str[0] != '-')
		return 0;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return 0;
		i++;
	}
	return (i > 1); // Asegura que hay al menos una 'n' después del '-'
}

int	missmatched_quotes(char *str)
{
	int	single;
	int	db_q;

	single = 0;
	db_q = 0;

	while (*str)
	{
		if (*str == '\'')
			single++;
		else if (*str =='"')
			db_q++;
		str++;
	}
	if (single % 2 != 0 || db_q % 2 != 0)
	{
		write(2, "echo: unmatched quote\n", 23);
		g_shell_status->error_code = 1;
		return (1);
	}
	return (0);
}

int builtin_echo(char **argv)
{
	int i;
	int newline;

	i = 1;
	newline = 1;
	while (argv[i] && is_n_flag(argv[i]))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		if (missmatched_quotes(argv[i]))
			return (1);
		write(1, argv[i], strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	g_shell_status->error_code = 0;
	return 0;
}