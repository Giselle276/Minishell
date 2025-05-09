/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:51:58 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/05/09 21:12:24 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	write_interactive_to_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return ;
	}
	close(fd);
}

void	handle_heredoc_no_cmd(const char *delimiter)
{
	char	*line;
	size_t	len;

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
		free(line);
	}
}

static void	fill_argv(char **argv, t_token *arg_token)
{
	int	i;

	i = 0;
	while (arg_token && i < 255)
	{
		argv[i] = ft_strdup(arg_token->value);
		if (!argv[i])
		{
			while (i > 0)
				free(argv[--i]);
			return ;
		}
		arg_token = arg_token->next;
		i++;
	}
	argv[i] = NULL;
}

int	exec_simple_command(t_cmds *ct, t_status *status)
{
	t_cmd	*cmd;
	char	*argv[256];
	int		fd;

	cmd = ct->parsed_simple;
	if (cmd->redir_in)
	{
		if (cmd->redir_in->type == T_REDIR_IN)
		{
			fd = open(cmd->redir_in->value, O_RDONLY);
			if (fd < 0)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd->redir_in->value, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				status->error_code = 1;
				return (1);
			}
		close(fd);
		}
	}
	if (!cmd->args && cmd->redir_in && cmd->redir_in->type == T_HEREDOC)
	{
		handle_heredoc_no_cmd(cmd->redir_in->value);
		return (0);
	}
	fill_argv(argv, cmd->args);
	if ((!cmd->args || !cmd->args->value) && cmd->redir_out && !cmd->redir_in)
	{
		write_interactive_to_file(cmd->redir_out->value); // o como accedas al nombre del archivo
		return (0);
	}
	if (!argv[0] || ft_strlen(argv[0]) == 0)
	{
		free_argv(argv);
		return (0);
	}
	if (is_assignment(argv[0]))
	{
		handle_assignment(argv[0], status);
		free_argv(argv);
		return (0);
	}
	if (is_builtin(argv[0]))
	{
		status->stat = exec_builtin_cmd(argv, cmd, status);
		return (status->stat);
	}
	exec_external_cmd(argv, cmd, status);
	return (0);
}
