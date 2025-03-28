/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:23:03 by cgil              #+#    #+#             */
/*   Updated: 2025/03/27 18:22:51 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//global variable
t_cmds	*g_ct; // declara un puntero a la estructura t_cmds

// se necesita variable global porque los manejadores
// de señales no pueden recibir argumentos personalizados
// y no se puede pasar la estructura t_cmds
// al manejador de señales

//static	void	signal_handler(int sgnl);

void	signal_handler(int sgnl)
{
	t_status	*last_stat;

	last_stat = g_ct->status;
	if (sgnl == SIGINT)
	{
		last_stat->error_code = SIGNT;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	if (sgnl == SIGQUIT)
	{
		last_stat->error_code = SQUIT;
		return ;
	}
}

void	handle_signal_before(void)
{
	signal(SIGINT, signal_c); // ctrl + c
	signal(SIGQUIT, SIG_IGN); // ctrl + \ no de segfault
}

void	handle_signal_after(t_cmds *ct)
{
	g_ct = ct;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void	signal_c(int sg)
{
	(void)sg;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
