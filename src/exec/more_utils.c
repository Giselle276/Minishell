/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:38:59 by claudia           #+#    #+#             */
/*   Updated: 2025/05/20 12:27:12 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	handle_single_redir_in(t_cmd *cmd, t_status *status)
{
	int	fd;

	if (cmd->redir_in && cmd->redir_in->type == T_REDIR_IN)
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
	return (0);
}

static int	handle_heredoc_no_args(t_cmd *cmd)
{
	if (!cmd->args && cmd->redir_in && cmd->redir_in->type == T_HEREDOC)
	{
		handle_heredoc_no_cmd(cmd->redir_in->value);
		return (1);
	}
	return (0);
}

static int	handle_redir_out_no_args(t_cmd *cmd)
{
	if ((!cmd->args || !cmd->args->value) && cmd->redir_out && !cmd->redir_in)
	{
		write_interactive_to_file(cmd->redir_out->value);
		return (1);
	}
	return (0);
}

static int	execute_command_logic(t_cmd *cmd, t_status *status)
{
	char	*argv[256];

	fill_argv(argv, cmd->args);
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
		status->error_code = exec_builtin_cmd(argv, cmd, status);
		return (status->error_code);
	}
	exec_external_cmd(argv, cmd, status);
	return (0);
}

int	exec_simple_command(t_cmds *ct, t_status *status)
{
	t_cmd	*cmd;

	cmd = ct->parsed_simple;
	if (handle_single_redir_in(cmd, status))
	{
		status->stat = status->error_code;
		return (status->error_code);
	}
	if (handle_heredoc_no_args(cmd))
		return (0);
	if (handle_redir_out_no_args(cmd))
		return (0);
	return (execute_command_logic(cmd, status));
}
