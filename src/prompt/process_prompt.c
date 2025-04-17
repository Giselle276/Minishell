/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:45:45 by cgil              #+#    #+#             */
/*   Updated: 2025/04/17 17:29:13 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	just_space(char *input, char c);

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
	prompt = USER_M "minishell>" RST;
	handle_signal_before();
	ct->cmd_line = readline(prompt);
	if (!ct->cmd_line)
	{
		exit (EXIT_SUCCESS);
	}
	if (just_space(ct->cmd_line, '\t') || just_space(ct->cmd_line, ' '))
	{
		add_history(ct->cmd_line);
		g_shell_status->error_code = 0;
	}
	else
		g_shell_status->error_code = EMPTYLINE;
}

static int	just_space(char *input, char c)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != c)
			return (1);
		i++;
	}
	return (0);
}
