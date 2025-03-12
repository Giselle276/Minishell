/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:09:13 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/03/11 19:22:34 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Función para validar la entrada del usuario
int validate_input(const char *input) {
	int open_single_quote = 0, open_double_quote = 0;
	for (int i = 0; input[i] != '\0'; i++) {
		if (input[i] == '\\' && !open_single_quote) {
			return 0; // Entrada inválida si hay una barra invertida fuera de comillas simples
		}
		if (input[i] == ';' && !open_single_quote) {
			return 0; // Entrada inválida si hay un punto y coma fuera de comillas simples
		}
		if (input[i] == '\"' && !open_single_quote) {
			open_double_quote ^= 1;
		}
		if (input[i] == '\'' && !open_double_quote) { // Aquí se corrige la comilla
			open_single_quote ^= 1;
		}
	}
	return !(open_single_quote || open_double_quote); // Verifica que las comillas estén cerradas
}


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

// Función para tokenizar la entrada respetando comillas
void parse_input(char *input, char **args) {
	int i = 0;
	char *ptr = input;
	while (*ptr) {
		while (*ptr == ' ') ptr++; // Omitir espacios iniciales
		if (*ptr == '\"' || *ptr == '\'') {
			char quote = *ptr++;
			args[i] = ptr;
			while (*ptr && *ptr != quote) ptr++;
			if (*ptr) *ptr++ = '\0';
		} else {
			args[i] = ptr;
			while (*ptr && *ptr != ' ') ptr++;
			if (*ptr) *ptr++ = '\0';
		}
		i++;
	}
	args[i] = NULL;
}

// Función principal del minishell
int main(void) {
	char *input;
	char *args[100];
	print_header();
	load_history();

	while (1) {
		input = readline(USER_M"✨🐚✨minishell$ "RST);

		if (!input) {
			printf("\nexit\n");
			break;
		}

		if (!validate_input(input)) {
			printf("Entrada inválida: no se permiten barras invertidas ni punto y coma, y las comillas deben cerrarse.\n");
			free(input);
			continue;
		}

		if (*input) {
			add_history(input);
			save_history();
		}

		parse_input(input, args);

		if (args[0])
			execute_command(args[0], args);

		free(input);
	}

}

