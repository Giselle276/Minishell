/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:14:00 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/03/25 17:30:20 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_builtin(char *cmd)
{
	int	flag;

	flag = 0;
	if (ft_strcmp("echo", cmd) || ft_strcmp("unset", cmd))
		flag = 1;
	if (ft_strcmp("exit", cmd) || ft_strcmp("export", cmd))
		flag = 1;
	if (ft_strcmp("cd", cmd) || ft_strcmp("env", cmd))
		flag = 1;
	if (ft_strcmp("pwd", cmd))
		flag = 1;
	return (flag);
}

void	token_type(t_token *first)
{
	t_token	*token;

	token = first;
	while (token != NULL)
	{
		if (check_builtin(token->value))
			token->type = BUILTIN;
		else if (ft_strcmp(">", token->value))
			token->type = REDIR_OUT;
		else if (ft_strcmp(">>", token->value))
			token->type = APPEND;
		else if (ft_strcmp("<", token->value))
			token->type = REDIR_IN;
		else if (ft_strcmp("<<", token->value))
			token->type = HEREDOC;
		else if (ft_strcmp(";", token->value))
			token->type = SEMICOLON;
		else if (ft_strcmp("|", token->value))
			token->type = PIPE;
		else
			token->type = TEXT;
		token = token->next;
	}
}


int	if_in_quote(char *str, char quote, char c)
{
	char	*fst_quote;
	char	*scnd_quote;
	int		flag;

	flag = 0;
	if ()
}
void	process_cmd(t_cmds	*cmd_tbl)
{
	if (piped_cmd(cmd_tbl->cmd_line)) && 
	
}

