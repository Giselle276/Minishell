/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:46:04 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/05/07 13:36:02 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	validate_path(char	*path, char **argv)
{
	(void) path;
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(*argv, 2);
	ft_putstr_fd("\n", 2);
}

void	error_denied(char **argv)
{
	ft_putstr_fd("minishell: permission denied: ", 2);
	ft_putstr_fd(*argv, 2);
	ft_putstr_fd("\n", 2);
}


