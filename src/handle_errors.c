/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:32:04 by claudia           #+#    #+#             */
/*   Updated: 2025/03/29 11:13:54 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_exit(t_errcode err_type)
{
	if (err_type == EUSAGE)
		printf("Run as: ./minishell\n");
	else if (err_type == EEOF)
	{
		printf("\nExiting shell\n");
		exit(EXIT_SUCCESS);
	}
	else if (err_type == EEOF)
		printf("\nError while allocating memory with malloc\n");
	exit(EXIT_FAILURE);
}