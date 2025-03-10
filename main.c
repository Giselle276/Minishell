/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-07 12:09:13 by gmaccha-          #+#    #+#             */
/*   Updated: 2025-03-07 12:09:13 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// Cargar historial desde un archivo
void load_history()
{
    if (read_history(HISTORY_FILE) != 0)
    {
        printf("No se pudo cargar el historial.\n");
    }
}

// Guardar historial en un archivo
void save_history()
{
    if (write_history(HISTORY_FILE) != 0)
    {
        printf("No se pudo guardar el historial.\n");
    }
}

// Buscar la ruta del ejecutable en la variable PATH
char *get_path(char *cmd)
{
    char *path = getenv("PATH"); // Obtener la variable PATH
    if (!path) return NULL;

    char *path_copy = strdup(path); // Copia porque strtok modifica la cadena
    char *dir = strtok(path_copy, ":"); // Separar por ":"
    char *full_path = NULL;

    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(cmd) + 2); // Reservar memoria
        if (!full_path)
            return NULL;

        sprintf(full_path, "%s/%s", dir, cmd); // Construir la ruta completa

        if (access(full_path, X_OK) == 0) // Verificar si es ejecutable
        {
            free(path_copy);
            return full_path; // Retornar la ruta del ejecutable
        }

        free(full_path);
        dir = strtok(NULL, ":"); // Siguiente directorio en PATH
    }

    free(path_copy);
    return NULL; // No encontrado
}

// Ejecutar un comando con fork y execve
void execute_command(char *cmd, char **args)
{
    pid_t pid = fork(); // Crear un proceso hijo

    if (pid == -1) // Error en fork
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) // Proceso hijo
    {
        if (strchr(cmd, '/') != NULL) // Si tiene '/' es ruta absoluta o relativa
        {
            execve(cmd, args, NULL);
        }
        else
        {
            char *path = get_path(cmd); // Buscar en PATH
            if (path)
            {
                execve(path, args, NULL);
                free(path);
            }
        }
        perror("execve"); // Si llega aquí, hubo un error
        exit(EXIT_FAILURE);
    }
    else // Proceso padre
    {
        waitpid(pid, NULL, 0); // Esperar al hijo
    }
}

// Función principal del minishell
int main(void)
{
    char *input;
    char *args[100];

    load_history(); // Cargar historial al inicio

    while (1)
    {
        input = readline("minishell> "); // Mostrar el prompt

        if (!input) // Detectar Ctrl+D (EOF) para salir
        {
            printf("\nexit\n");
            break;
        }

        if (*input) // Si el comando no está vacío
        {
            add_history(input);  // Agregar al historial en memoria
            save_history();      // Guardar el historial en el archivo
        }

        // Tokenizar la entrada en argumentos
        int i = 0;
        char *token = strtok(input, " ");
        while (token && i < 99)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Ejecutar el comando si hay algo escrito
        if (args[0])
            execute_command(args[0], args);

        free(input); // Liberar memoria de readline
    }

    return 0;
}

