/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:46:04 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/05/20 21:46:51 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	validate_path(char *path, char **argv)
{
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(*argv, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

void	error_denied(char **argv)
{
	ft_putstr_fd("minishell: permission denied: ", 2);
	ft_putstr_fd(*argv, 2);
	ft_putstr_fd("\n", 2);
}
