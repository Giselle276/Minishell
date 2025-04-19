/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:09:13 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/04/19 21:13:04 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_status	*g_shell_status;

int	main(int ac, char *av[], char *envp[])
{
	(void) av;
	if (ac != 1)
		validate_error(EUSAGE, "Run as: ./minishell\n", NULL);
	
	// Debug: Imprimir el contenido de envp al principio
    int i = 0;
    while (envp[i]) {
        printf("envp[%d]: %s\n", i, envp[i]);
        i++;
    }
	
	g_shell_status = init_shell(envp);
	print_header();
	shell_loop();
	free_shell(g_shell_status);
	return (EXIT_SUCCESS);
}
