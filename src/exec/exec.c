/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:08:03 by cgil              #+#    #+#             */
/*   Updated: 2025/04/19 17:12:26 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_root(t_status *st, t_cmds *ct)
{
	ct->status = st;
	if (ct->parsed_simple)
		exec_simple_command(ct);
	else if (ct->parsed_cmds)
		exec_pipeline(ct);
}

/*
int	exec_pipeline(t_cmds *ct)
{
	int		i;
	int		pipefd[2];
	int		prev_fd;
	pid_t	pid;
	t_cmd	**cmds;
	t_token	*arg;
	char	*argv[256];
	int		j;
	int		waited;

	i = 0;
	prev_fd = -1;
	cmds = ct->parsed_cmds;
	while (cmds[i])
	{
		pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (cmds[i + 1])
			{
				dup2(pipefd[1], STDOUT_FILENO);
			}
			close(pipefd[0]);
			close(pipefd[1]);
			handle_redirections(cmds[i]);
			// construir argv
			arg = cmds[i]->args;
			j = 0;
			while (arg && j < 255) // // no se necesita, ya estan los tokens separados en la estructura
			{
				argv[j++] = arg->value;
				arg = arg->next;
			}
			argv[j] = NULL;
			execvp(argv[0], argv); // no se puede usar
			perror("execvp");
			exit(127);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		i++;
	}
	waited = 0;
	while (waited < i)
	{
		wait(NULL);
		waited++;
	}
	return (0);
}

*/

void	handle_redirections(t_cmd *cmd)
{
	t_token	*redir;
	int		fd;

	// Última redirección de entrada
	redir = cmd->redir_in;
	while (redir && redir->next)
		redir = redir->next;
	if (redir)
	{
		if (redir->type == T_REDIR_IN)
			fd = open(redir->value, O_RDONLY);
		else if (redir->type == T_HEREDOC)
			fd = open("/tmp/.heredoc_tmp", O_RDONLY);
		else
			fd = -1;
		if (fd < 0)
		{
			perror("Redirección de entrada");
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}

	// Última redirección de salida
	redir = cmd->redir_out;
	while (redir && redir->next)
		redir = redir->next;
	if (redir)
	{
		if (redir->type == T_REDIR_OUT)
			fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == T_APPEND)
			fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = -1;
		if (fd < 0)
		{
			perror("Redirección de salida");
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
