/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42madrid.com>           #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-17 10:51:52 by cgil              #+#    #+#             */
/*   Updated: 2025-03-17 10:51:52 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int validate_input(const char *input) {
	int open_single_quote = 0, open_double_quote = 0;
	for (int i = 0; input[i] != '\0'; i++) {
		if (input[i] == '\\' && !open_single_quote) {
			return 0; // Entrada inválida si hay una barra invertida fuera de comillas simples
		}
		if (input[i] == ';' && !open_single_quote) {
			return 0; // Entrada inválida si hay un punto y coma fuera de comillas simples
		}
		if (input[i] == '\"' && !open_single_quote) {
			open_double_quote ^= 1;
		}
		if (input[i] == '\'' && !open_double_quote) { // Aquí se corrige la comilla
			open_single_quote ^= 1;
		}
	}
	return !(open_single_quote || open_double_quote); // Verifica que las comillas estén cerradas
}
