/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-15 12:40:37 by gmaccha-          #+#    #+#             */
/*   Updated: 2025-03-15 12:40:37 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int parse_iredirect(t_process *p, t_token **tk, int i[], t_bool r_only)
{
    t_token *token;
    t_file *input;

    // Avanzamos al siguiente token (esperamos que sea el nombre del archivo)
    *tk = (*tk)->next;
    token = *tk;

    // Si el siguiente token no es una palabra (nombre de archivo), retorna error
    if (token->type != TEXT)
        return (EPARSE);

    // Reservamos memoria para la estructura t_file que almacenará la redirección
    input = malloc(sizeof(t_file));
    if (!input)
        return (ft_check_error(EALLOC, "Allocating input", NULL)); // Manejo de error si malloc falla

    // Guardamos la ruta del archivo en input->path
    input->path = ft_strdup(token->value);
    input->fd = -1; // Inicializamos el descriptor de archivo como -1 (aún no abierto)

    // Si r_only es true, significa que es un heredoc (<<)
    if (r_only == true)
        input->flags = 2; // Flags 2 para indicar heredoc (<<)

    // Si r_only es false, significa que es una redirección estándar (<)
    else if (r_only == false)
    {
        input->flags = 1; // Flags 1 para indicar entrada estándar (<)

        // Se almacena el archivo en argv del proceso (con prefijo "/tmp/" si es necesario)
        p->argv[i[I_ARGV]] = ft_join_var(2, "/tmp/", token->value);
        i[I_ARGV]++; // Se incrementa el índice de argumentos
    }

    // Se guarda el archivo en la lista de archivos de entrada del proceso
    p->input_file[i[I_IRED]] = input;
    i[I_IRED]++; // Se incrementa el índice de archivos de entrada

    return (0); // Retorna 0 si todo salió bien
}

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
		if (temp->type == REDIR_IN) // Si es una redirección de entrada "<"
			parse_iredirect(process, &temp, i, true);
		else if (temp->type == HEREDOC) // Si es una redirección especial "<<" (heredoc)
			parse_iredirect(process, &temp, i, false);
		else if (temp->type == REDIR_OUT) // Si es una redirección de salida ">"
			parse_oredirect(process, &temp, false, i);
		else if (temp->type == APPEND) // Si es una redirección de salida en modo ">>"
			parse_oredirect(process, &temp, true, i);
		else // Si es parte del comando (nombre o argumento)
			parse_words(process, temp, i);

		temp = temp->next; // Avanza al siguiente token
	}

	free(i); // Libera la memoria de los índices
	return (process); // Devuelve el proceso con la información cargada
}

