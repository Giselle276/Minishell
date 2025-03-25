/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42madrid.com>           #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-25 16:45:45 by cgil              #+#    #+#             */
/*   Updated: 2025-03-25 16:45:45 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    process_prompt(t_cmds *ct)
{
    char        *prompt;
    t_status    *status;

    status = ct->status;
    if (status->error_code == ECMDNF || status-> error_code == SINT
            || status-> error_code == SQUIT)
        status->stat = status->error_code = 1; // ante cualquier error, marca errcode en 1
    prompt = print_prompt();
	empty_line();
	ct->cmd_line = readline(prompt);
	if (!ct->cmd_line)
		exit_shell(SIGEXIT,ct);
	else if (not_empy_line())

}
/*void	exit_shell(t_errcode err, t_cmds *ct)
{
	t_status	*status;

	status = NULL;
	if (ct != NULL)
	{
		status = ct->status;
		//before_leaving(ct); // to do // liberar memoria entes de poner otro prompt
	}
	if (status)
		//free_status(status); // finish
	exit(err);
}*/

void	print_prompt(void)
{
	printf("Minishell >");
}

