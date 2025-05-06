/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:45:45 by cgil              #+#    #+#             */
/*   Updated: 2025/05/06 18:47:05 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_empty_line(char *input);

void	process_prompt(t_cmds *ct, t_status *status)
{
	char		*prompt;

	if (status->error_code == ECMDNF
		||status->error_code == SIGNT
		|| status->error_code == SQUIT)
	{
		status->error_code = 1;
		status->stat = 1;
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
		status->error_code = EMPTYLINE;
		free(ct->cmd_line);
		ct->cmd_line = NULL;
	}
	else
		add_history(ct->cmd_line);
	status->error_code = 0;
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
