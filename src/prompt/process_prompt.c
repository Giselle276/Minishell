/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:45:45 by cgil              #+#    #+#             */
/*   Updated: 2025/05/27 12:11:41 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_empty_line(char *input);

static void	handle_empty_line(char **line, t_status *status)
{
	status->error_code = EMPTYLINE;
	free(*line);
	*line = NULL;
}

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
		handle_empty_line(&ct->cmd_line, status);
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
