/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:32:04 by claudia           #+#    #+#             */
/*   Updated: 2025/04/11 11:23:12 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	validate_error(t_errcode err_code, char *err, t_cmds *ct)
{
	(void)ct;
	if (err_code == EUSAGE || err_code == EALLOC)
	{
		print_err(err, err_code);
	}
	else if (err_code > 0)
	{
		print_err(err, 0);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	return (err_code);
}

void	print_err(char *err, int err_code)
{
	if (err)
		ft_putstr_fd(err, STDERR_FILENO);
	if (err_code)
		exit(err_code);
}
