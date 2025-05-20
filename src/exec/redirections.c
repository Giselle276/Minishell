/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:46:02 by claudia           #+#    #+#             */
/*   Updated: 2025/05/20 12:27:39 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_input_redirection(t_token *redir_in, t_status *status)
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
				status->error_code = 1;
				return (1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		redir_in = redir_in->next;
	}
	return (0);
}

static int	handle_output_redirection(t_token *redir_out, t_status *status)
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
			status->error_code = 1;
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		redir_out = redir_out->next;
	}
	return (0);
}

int	handle_redirections(t_cmd *cmd, t_status *status)
{
	if (handle_input_redirection(cmd->redir_in, status))
		return (1);
	if (handle_output_redirection(cmd->redir_out, status))
		return (1);
	return (0);
}
