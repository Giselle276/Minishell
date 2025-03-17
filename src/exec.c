/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:08:03 by cgil              #+#    #+#             */
/*   Updated: 2025/03/17 18:49:23 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Buscar la ruta del ejecutable en la variable PATH sin strtok
char *get_path(char *cmd) {
	char *path = getenv("PATH");
	if (!path) return NULL;

	char *path_copy = strdup(path);
	if (!path_copy) return NULL;

	char *dir = path_copy;
	char *full_path = NULL;

	while (dir) {
		char *next = strchr(dir, ':'); // Encontrar el próximo ':'
		if (next) *next = '\0'; // Reemplazar ':' temporalmente con '\0'

		full_path = malloc(strlen(dir) + strlen(cmd) + 2);
		if (!full_path) {
			free(path_copy);
			return NULL;
		}

		sprintf(full_path, "%s/%s", dir, cmd);

		if (access(full_path, X_OK) == 0) {
			free(path_copy);
			return full_path;
		}

		free(full_path);
		if (!next) break; // Si no hay más ':', salir del bucle
		dir = next + 1; // Mover al siguiente directorio
	}

	free(path_copy);
	return NULL;
}

// Ejecutar un comando con fork y execve
void execute_command(char *cmd, char **args) {
	pid_t pid = fork();

	if (pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		if (strchr(cmd, '/') != NULL) {
			execve(cmd, args, NULL);
		} else {
			char *path = get_path(cmd);
			if (path) {
				execve(path, args, NULL);
				free(path);
			}
		}
		perror("execve");
		exit(EXIT_FAILURE);
	} else {
		waitpid(pid, NULL, 0);
	}
}
