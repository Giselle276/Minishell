/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:46:02 by claudia           #+#    #+#             */
/*   Updated: 2025/05/16 15:46:10 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_input_redirection(t_token *redir_in)
{
	int	fd;

	while (redir_in)
	{
		if (redir_in->type == T_HEREDOC)
			handle_heredoc(redir_in->value);
		else
		{
			fd = open(redir_in->value, O_RDONLY);
			if (fd < 0)
			{
				perror(redir_in->value);
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		redir_in = redir_in->next;
	}
}

static void	handle_output_redirection(t_token *redir_out)
{
	int	fd;

	while (redir_out)
	{
		if (redir_out->type == T_APPEND)
			fd = open(redir_out->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(redir_out->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(redir_out->value);
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		redir_out = redir_out->next;
	}
}

void	handle_redirections(t_cmd *cmd)
{
	handle_input_redirection(cmd->redir_in);
	handle_output_redirection(cmd->redir_out);
}
