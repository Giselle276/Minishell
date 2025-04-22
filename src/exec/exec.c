/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:08:03 by cgil              #+#    #+#             */
/*   Updated: 2025/04/22 12:18:05 by gmaccha-         ###   ########.fr       */
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
		exit(1);
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
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_redirections(t_cmd *cmd)
{
	handle_redir_in(cmd->redir_in);
	handle_redir_out(cmd->redir_out);
}

