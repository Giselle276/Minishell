/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:09:13 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/05/06 09:50:36 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	t_status	*status;

	(void) av;
	if (ac != 1)
		validate_error(EUSAGE, "Run as: ./minishell\n", NULL);
	status = init_shell(envp);
	print_header();
	shell_loop(status);
	free_shell(status);
	return (EXIT_SUCCESS);
}
