/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42madrid.com>           #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-17 11:04:57 by cgil              #+#    #+#             */
/*   Updated: 2025-03-17 11:04:57 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//reemplazar porque no estan permitidas!!!!!!!!!!!

// Cargar historial desde un archivo
void load_history() {
	if (read_history(HISTORY_FILE) != 0) {
		//printf("No se pudo cargar el historial.\n");
	}
}

// Guardar historial en un archivo
void save_history() {
	if (write_history(HISTORY_FILE) != 0)
	{
	}
}
