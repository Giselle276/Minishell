/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:09:13 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/03/22 19:26:00 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(void)
{
	char *input;
	char *args[100];
	
	print_header();
	while (1) 
	{
		input = readline(USER_M"✨minishell$ "RST);
		if (!input) 
		{
			printf("\nexiting shell\n"); // ctrl + d
			break;
		}
		if (!validate_input(input)) 
		{
			printf("Invalid input, check correct use of the minishell\n");
			free(input);
			continue;
		}
		if (*input)
			add_history(input);
		//parse_input(input, args);
		if (args[0])
			execute_command(args[0], args);
		free(input);
	}
}

/*int main (int argc, char *argv[], char *envp[])
{
	//t_status	*shell_status;

	(void) argv;
	(void)*envp;
	if (argc != 1)
		print_error("Run as : ./minishell");
	//shell_status = init_shell(envp);
	print_header();
	//run_shell(shell_status);
	//clean_shell(shell_status);
	return (EXIT_SUCCESS);
}*/