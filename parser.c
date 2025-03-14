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

t_process	*parse_command(t_token **tokens)
{
	t_process	*process;
	int			*i;
	t_token		*temp;

	process = ft_calloc(1, sizeof(t_process)); // Reserva memoria para `t_process`
	i = ft_calloc(4, sizeof(int)); // Reserva memoria para índices de argumentos
	if (!process) // Verifica si la asignación falló
		return (NULL);

	temp = *tokens; // Apunta al primer token del comando

	while (temp != NULL) // Recorre la lista de tokens
	{
		if (temp->type == T_IREDIRECT) // Si es una redirección de entrada "<"
			parse_iredirect(process, &temp, i, true);
		else if (temp->type == T_IREADNOHISTORY) // Si es una redirección especial "<<" (heredoc)
			parse_iredirect(process, &temp, i, false);
		else if (temp->type == T_OREDIRECT) // Si es una redirección de salida ">"
			parse_oredirect(process, &temp, false, i);
		else if (temp->type == T_OAPPEND) // Si es una redirección de salida en modo ">>"
			parse_oredirect(process, &temp, true, i);
		else // Si es parte del comando (nombre o argumento)
			parse_words(process, temp, i);

		temp = temp->next; // Avanza al siguiente token
	}

	free(i); // Libera la memoria de los índices
	return (process); // Devuelve el proceso con la información cargada
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
