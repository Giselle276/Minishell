/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:28:05 by claudia           #+#    #+#             */
/*   Updated: 2025/04/22 13:03:49 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	shell_loop(void)
{
	t_cmds	*cmds_table;

	while (1)
	{
		cmds_table = init_cmds_table(g_shell_status);
		process_prompt(cmds_table);
		if (g_shell_status->error_code == 0)
			tokenizing(cmds_table);
		if (g_shell_status->error_code == 0)
			expand_env_vars(cmds_table->token_lst, g_shell_status);
		if (g_shell_status->error_code == 0)
		{
			parser(cmds_table);
			execute_root(g_shell_status, cmds_table);
		}
		free_cmds_table(cmds_table);
	}
}
