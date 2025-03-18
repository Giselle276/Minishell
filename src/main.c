/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:09:13 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/03/17 18:49:36 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(void) {
	char *input;
	char *args[100];
	print_header();
	load_history();

	while (1) {
		input = readline(USER_M"✨minishell$ "RST);
		if (!input) {
			printf("\nexit\n");
			break;
		}
		if (!validate_input(input)) {
			printf("Entrada inválida: no se permiten barras invertidas ni punto y coma, y las comillas deben cerrarse.\n");
			free(input);
			continue;
		}
		if (*input) {
			add_history(input);
			save_history();
		}
		parse_input(input, args);
		if (args[0])
			execute_command(args[0], args);
		free(input);
	}
}

