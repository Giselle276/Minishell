/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:46:02 by claudia           #+#    #+#             */
/*   Updated: 2025/04/24 19:15:10 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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