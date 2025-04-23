/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:45:45 by cgil              #+#    #+#             */
/*   Updated: 2025/04/23 12:36:22 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_empty_line(char *input);

void	process_prompt(t_cmds *ct)
{
	char		*prompt;

	if (g_shell_status->error_code == ECMDNF
		|| g_shell_status->error_code == SIGNT
		|| g_shell_status->error_code == SQUIT)
	{
		g_shell_status->error_code = 1;
		g_shell_status->stat = 1;
	}
	prompt = USER_M "minishell> " RST;
	handle_signal_before();
	ct->cmd_line = readline(prompt);
	if (!ct->cmd_line)
	{
		printf("exit\n");
		exit (EXIT_SUCCESS);
	}
	if (is_empty_line(ct->cmd_line))
	{
		g_shell_status->error_code = EMPTYLINE;
		//ct->cmd_line = NULL;
	}
	add_history(ct->cmd_line);
	g_shell_status->error_code = 0;
}

static int	is_empty_line(char *input)
{
	while (*input)
	{
		if (*input != ' ' && *input != '\t')
			return (0);
		input++;
	}
	return (1);
}
