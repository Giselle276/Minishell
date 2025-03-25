/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42madrid.com>           #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-25 17:23:03 by cgil              #+#    #+#             */
/*   Updated: 2025-03-25 17:23:03 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	empty_line(void)
{
	signal(SIGINT, re_prompt); // ctrl + c
	signal(SIGQUIT, SIG_IGN); // ctrl + \ no de segfault
}

void	re_prompt(int sg)
{
	(void)sg;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
