/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:45:45 by cgil              #+#    #+#             */
/*   Updated: 2025/03/27 17:18:02 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	just_space(char *input, char c);

void	process_prompt(t_cmds *ct)
{
	t_status	*status;

    status = ct->status;
    if (status->error_code == ECMDNF || status-> error_code == SIGNT || status-> error_code == SQUIT)
		status->stat = status->error_code = 1; // ante cualquier error, marca errcode en 1 // ver en donde se maneja 
	printf(USER_M"✨minishell$ "RST);
	handle_signal_before(); // señales antes de recibir input
	ct->cmd_line = readline("");
	if (!ct->cmd_line)
		exit_shell(SIGEXIT,ct); // to do // ctrl + d
	if (just_space(ct->cmd_line, '\t') && just_space(ct->cmd_line, ' ')) // si la linea se agrega al historial
	{
		add_history(ct->cmd_line);
		status->stat = 0;
	}
	else
		status->error_code = EMPTYLINE;
	handle_signal_after(ct);
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
