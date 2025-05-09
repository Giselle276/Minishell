/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:46:02 by claudia           #+#    #+#             */
/*   Updated: 2025/05/09 21:35:07 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*void	handle_heredoc(const char *delimiter)
{
	char	*line;
	int		pipefd[2];
	size_t	len;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	while (1)
	{
		write(STDOUT_FILENO, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& ft_strlen(line) == ft_strlen(delimiter))
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}*/



/*void	handle_redirections(t_cmd *cmd)
{
	t_token	*tmp;
	int		fd;

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
}*/

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
