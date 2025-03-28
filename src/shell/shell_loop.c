/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:28:05 by claudia           #+#    #+#             */
/*   Updated: 2025/03/27 16:14:44 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void shell_loop(t_status *shell_status)
{
	t_cmds  *cmds_table;

	while (1) // seguir recibiendo comandos
	{
		cmds_table = init_cmds_table(shell_status); // inicializar estructura de la tabla de comandos
		process_prompt(cmds_table);
		if (shell_status->error_code == 0)
			//tokenizer(cmds_table); // to do
		//if (shell_status->error_code == 0 && !(token_error(cmds_table))) // -> to do
		{
			//shell_status->process_lst = parser(cmds_table);
			// execute_root(shell_status, cmds_table); // to do
		}
	// free_shell(cmds_table); // to do
	}
}
