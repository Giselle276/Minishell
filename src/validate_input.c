/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:51:52 by cgil              #+#    #+#             */
/*   Updated: 2025/03/22 17:12:44 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int validate_input(const char *input) 
{
	int i;
	int open_single_quote; // abierta 1 cerrada 0
	int open_double_quote;

	i = 0;
	open_single_quote = 0; // cerradas 
	open_double_quote = 0; // cerradas 
	while (input[i] != '\0') 
	{
		if (input[i] == '\\' && !open_single_quote)
			return 0; // Entrada inválida
		if (input[i] == ';' && !open_single_quote)
			return 0; // Entrada inválida 
		if (input[i] == '\"' && !open_single_quote)
			open_double_quote ^= 1;
		if (input[i] == '\'' && !open_double_quote)
			open_single_quote ^= 1;
		i++;
	}
	return !(open_single_quote || open_double_quote); // Verifica que las comillas estén cerradas
}