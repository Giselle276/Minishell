/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-11 12:20:18 by gmaccha-          #+#    #+#             */
/*   Updated: 2025-03-11 12:20:18 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void push_process(t_process **lst, t_process *new_process)
{
    t_process *last;

    if (*lst == NULL) // Si la lista está vacía
        *lst = new_process; // El nuevo proceso es la cabeza
    else
    {
        last = *lst; // Apunta al primer proceso de la lista
        while (last->next != NULL) // Busca el último nodo
            last = last->next;

        last->next = new_process; // Conecta el nuevo proceso al final
        new_process->prev = last; // Establece el puntero hacia atrás
    }
}

t_process	*simple_or_piped(t_token **tokens, int flag)
{
	t_process	*head;
	t_process	*command;
	t_process	*process_lst;

	head = NULL; // Inicializa la lista de procesos

	if (flag == 1) // Si hay un pipeline (más de un comando)
	{
		while (tokens[flag] != NULL) // Recorre cada comando en el pipeline
		{
			command = parse_command(&tokens[flag]); // Parsea un comando
			push_process(&head, command); // Agrega el proceso a la lista
			flag++;
		}
	}
	else // Si es un comando simple (sin `|`)
	{
		command = parse_command(tokens); // Parsea el comando
		push_process(&head, command); // Agrega el proceso a la lista
	}

	process_lst = head; // Asigna la cabeza de la lista
	return (process_lst); // Devuelve la lista de procesos
}

t_process	*parser(t_cmd_tab *tb)
{
	t_token		**tokens;
	int			flag;
	t_process	*process;

	flag = 0;// comando simple por defecto
	if (tb->piped_cmd != NULL)
	{
		tokens = tb->piped_cmd;
		flag = 1;
	}
	else
		tokens = &tb->simple_cmd;
	process = simple_or_piped(tokens, flag);
	return (process);
}
