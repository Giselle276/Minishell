/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:46:02 by claudia           #+#    #+#             */
/*   Updated: 2025/05/05 17:44:55 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
/*
static void	handle_redir_in(t_token *redir)
{
	int	fd;

	while (redir && redir->next)
		redir = redir->next;
	if (!redir)
		return ;
	if (redir->type == T_REDIR_IN)
		fd = open(redir->value, O_RDONLY);
	else if (redir->type == T_HEREDOC)
		fd = open("/tmp/.heredoc_tmp", O_RDONLY);
	else
		fd = -1;
	if (fd < 0)
	{
		perror("Redirección de entrada");
		return ;
		//exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	handle_redir_out(t_token *redir)
{
	int	fd;

	while (redir && redir->next)
		redir = redir->next;
	if (!redir)
		return ;
	if (redir->type == T_REDIR_OUT)
		fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == T_APPEND)
		fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	if (fd < 0)
	{
		perror("Redirección de salida");
		//exit(1);
		return ;
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_redirections(t_cmd *cmd)
{
	handle_redir_in(cmd->redir_in);
	handle_redir_out(cmd->redir_out);
}
*/

void	handle_heredoc(const char *delimiter)
{
   char    *line;
    int     pipefd[2];

    // Crear el pipe
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    while (1)
    {
        // Solicitar al usuario que ingrese una línea
        write(STDOUT_FILENO, "heredoc> ", 9);
        
        // Leer la línea de entrada
        line = get_next_line(STDIN_FILENO); // Utiliza tu función get_next_line o getline
        if (!line)
        {
            break; // Si no hay línea, terminamos
        }

        // Eliminar el salto de línea (si existe) al final de la línea
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0'; // Elimina el salto de línea
        }

        // Verificar si la línea es igual al delimitador
        if (ft_strncmp(line, delimiter, strlen(delimiter)) == 0 && strlen(line) == strlen(delimiter))
        {
            free(line); // Liberamos la memoria de la línea
            break; // Si coincide con el delimitador, terminamos el heredoc
        }

        // Escribir la línea en el pipe
        write(pipefd[1], line, strlen(line));
        write(pipefd[1], "\n", 1); // Aseguramos que se escriba un salto de línea
        free(line); // Liberamos la memoria de la línea
    }

    // Cerrar el descriptor de escritura del pipe
    close(pipefd[1]);

    // Redirigir la entrada estándar al pipe
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]); // Cerrar el descriptor de lectura del pipe
}


void	handle_redirections(t_cmd *cmd)
{
	t_token	*tmp;
	int		fd;

	// Redirección de salida (>, >>)
	tmp = cmd->redir_out;
	while (tmp)
	{
		if (tmp->type == T_APPEND)
			fd = open(tmp->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(tmp->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(tmp->value);
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		tmp = tmp->next;
	}

	// Redirección de entrada (<, <<)
	tmp = cmd->redir_in;
	while (tmp)
	{
		if (tmp->type == T_HEREDOC)
			handle_heredoc(tmp->value);
		else
		{
			fd = open(tmp->value, O_RDONLY);
			if (fd < 0)
			{
				perror(tmp->value);
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		tmp = tmp->next;
	}
}
