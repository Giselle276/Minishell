/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:09:13 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/04/11 10:46:43 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	t_status	*shell_status;

	(void) av;
	if (ac != 1)
		validate_error(EUSAGE, "Run as: ./minishell\n", NULL);
	shell_status = init_shell(envp);
	print_header();
	shell_loop(shell_status);
	//free_shell(shell_status);
	return (EXIT_SUCCESS);
}
