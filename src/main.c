/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:09:13 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/04/30 15:56:52 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char *av[], char *envp[])
{
	t_status *status;
	
	(void) av;
	if (ac != 1)
		validate_error(EUSAGE, "Run as: ./minishell\n", NULL);
	status = init_shell(envp);
	print_header();
	shell_loop(status);
	free_shell(status);
	return (EXIT_SUCCESS);
}
