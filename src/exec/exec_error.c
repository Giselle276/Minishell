/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:46:04 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/05/16 15:47:33 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	validate_path(char *path, char **argv)
{
	if (!path || access(path, F_OK) != 0)
	{
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		ft_putstr_fd(*argv, 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(*argv, 2);
		ft_putstr_fd("\n", 2);
	}
}

void	error_denied(char **argv)
{
	ft_putstr_fd("minishell: permission denied: ", 2);
	ft_putstr_fd(*argv, 2);
	ft_putstr_fd("\n", 2);
}
