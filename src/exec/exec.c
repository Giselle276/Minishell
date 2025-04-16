/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:08:03 by cgil              #+#    #+#             */
/*   Updated: 2025/04/16 14:38:39 by gmaccha-         ###   ########.fr       */
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

int exec_simple_command(t_cmds *ct)
{
	t_cmd *cmd = ct->parsed_simple;
	t_token *arg_token = cmd->args;
	char *argv[256];
	int i = 0;

	while (arg_token && i < 255) {
		argv[i++] = strdup(arg_token->value);
		arg_token = arg_token->next;
	}
	argv[i] = NULL;
	if (!argv[0])
		return (0);
	if (is_builtin(argv[0]))
	{
		int saved_stdin = dup(STDIN_FILENO);
		int saved_stdout = dup(STDOUT_FILENO);

		handle_redirections(cmd); // redirecciones en el proceso actual
		if (!ct->status->envp || !ct->status->envp[0])
			printf("envp en exec_simple_command: %p\n", (void *)ct->status->envp);
		ct->status->stat = exec_builtin(argv, ct->status);

		// Restaurar entrada/salida estándar
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		int j = 0;
		while (argv[j])
			free(argv[j++]);
		return (ct->status->stat);
	}

	
	pid_t pid = fork();
	if (pid == 0) {
		handle_redirections(cmd);
		execvp(argv[0], argv);
		perror("execvp");
		exit(127);
	}
	else if (pid > 0)
	{
		int	status;
		waitpid(pid, &status, 0);
		ct->status->stat = WEXITSTATUS(status);
	} 
	else
	{
		perror("fork");
	}
	return (0);
}


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
			while (arg && j < 255)
			{
				argv[j++] = arg->value;
				arg = arg->next;
			}
			argv[j] = NULL;

			execvp(argv[0], argv);
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
	// Esperar a todos los hijos
	waited = 0;
	while (waited < i)
	{
		wait(NULL);
		waited++;
	}
	return (0);
}

void	handle_redirections(t_cmd *cmd)
{
	t_token		*redir;
	int			fd;

	// Redirecciones de entrada
	redir = cmd->redir_in;
	while (redir)
	{
		if (redir->type == T_REDIR_IN)
			fd = open(redir->value, O_RDONLY);
		else if (redir->type == T_HEREDOC)
			fd = open("/tmp/.heredoc_tmp", O_RDONLY); // ejemplo
		else
			fd = -1;

		if (fd < 0) 
		{
			perror("Redirección de entrada");
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		redir = redir->next;
	}

	// Redirecciones de salida
	redir = cmd->redir_out;
	while (redir) {
		int fd;
		if (redir->type == T_REDIR_OUT)
			fd = open(redir->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == T_APPEND)
			fd = open(redir->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = -1;

		if (fd < 0) {
			perror("Redirección de salida");
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
}

bool	is_builtin(const char *cmd)
{
	if (!cmd)
		return (false);
	return (
		ft_strcmp(cmd, "cd") == 0 ||
		ft_strcmp(cmd, "echo") == 0 ||
		ft_strcmp(cmd, "exit") == 0 ||
		ft_strcmp(cmd, "pwd") == 0 ||
		ft_strcmp(cmd, "env") == 0
	);
}
int	exec_builtin(char **argv, t_status *status)
{
	if (ft_strcmp(argv[0], "cd") == 0)
		return (builtin_cd(argv, status));
	else if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argv));
	else if (ft_strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argv));
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(argv[0], "env") == 0)
		return (builtin_env(status->envp));
	return (1);
}
