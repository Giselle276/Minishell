/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:28:05 by claudia           #+#    #+#             */
/*   Updated: 2025/03/25 17:15:33 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//read-eval-print-loop

void shell_loop(t_status *shell_status)
{
    t_cmds  *cmds_table;
    
    while (1) // seguir recibiendo comandos
    {
        cmds_table = init_cmds_table(shell_status); // inicializar estructura de la tabla de comandos
        process_prompt(cmds_table);
        if (shell_status->error_code == 0)
            tokenizer(cmds_table); // to do
        if (shell_status->error_code == 0 && !(token_error(cmds_table)))
        {
            //shell_status->process_lst = parser(cmds_table);
            execute_root(shell_status, cmds_table); // to do
        }
        free_shell(cmds_table);
    }
}

void    process_prompt(t_cmds *ct)
{
    char        *prompt;
    t_status    *status;

    status = ct->status; 
    if (status->error_code == ECMDNF || status-> error_code == SINT 
            || status-> error_code == SQUIT)
        status->stat = status->error_code = 1; // ante cualquier error, marca errcode en 1
    prompt = get_prompt();
}


t_cmds  *init_cmds_table(t_status *shell_st)
{
    t_cmds  *cmds_table;

    cmds_table = (t_cmds *)malloc(sizeof(t_cmds));
    if (!cmds_table)
        error_exit(EALLOC);
    cmds_table->status = shell_st;
    cmds_table->cmd_line = NULL;
    cmds_table->cmd_splitted = NULL;
    cmds_table->piped_cmd = NULL;
    cmds_table->simple_cmd = NULL;
    return (cmds_table);
}