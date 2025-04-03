/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:21:25 by cgil              #+#    #+#             */
/*   Updated: 2025/04/02 20:00:40 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//static int	ft_is_space(char c);

int	check_only_char(char *str, char look)
{
	while (*str)
	{
		if (*str != look)
			return (1); // habia un caracter distinto
		str++;
	}
	return (0); // solo habia look
}

int	validate_piped_cmd(char *line)
{
	char	*pipe;

	if (!ft_strchr(line, T_PIPE));
		return (0);
	pipe = ft_strchr(line, T_PIPE); // posicion del primer pipe
	if (ft_strlen(pipe) <= 1) // ver si el pipe es el ultimo caracter
		return (0);
	if ((*(pipe + 2) == '|' || *(pipe  + 1) == '|' || !check_only_char(pipe + 1, ' ')))
		return (0);
	return (1);
}

void	tokenizing(t_cmds *ct)
{
	if (validate_piped_cmd(ct->cmd_line))
		ct->piped_cmd = piped_cmd(ct->cmd_line);
	else
		ct->not_piped_cmd = split_tk(ct->cmd_line, T_SPACE, ct);
	return ; 
}

t_token	*split_tk(char *cmd, char delimiter, t_cmds *ct)
{
	
}
/*static int	check_builtin(char *cmd)
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
}*/

/*void	tokenizer(t_token *first)
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
}*/

/*debe dividir la línea de comandos (cmds_table->cmd_line) 
en una lista enlazada de t_token.*/

/*t_token	*get_tokens(char *cmd_line)
{
	t_token *head;
	t_token *new_token;
	char 	*word;
	int 	i;

	head = NULL;
	i = 0;
	while (cmd_line[i])
	{
		while (cmd_line[i] && ft_is_space(cmd_line[i]))
			i++;
		if (!cmd_line[i])
			break;
		word = get_next_tk(&cmd_line[i]);
		if (!word)
			return (NULL);
		new_token = create_tk(word);
		add_tk_list(&head, new_token);
		i += ft_strlen(word);
		free(word);
	}
	return (head);
}

t_token	*create_tk(char *token)
{
	t_token *new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = token;
	new_token->type = 0; // ? ver como inicializar
	new_token->next = NULL;
	return (new_token);
	
}*/

/*/ obtiene el siguiente token
y devuelve una copia de el*/

/*char *get_next_tk(char **cmd_line)
{
	char *start;
	char *token;
	int  len;

	len = 0;
	while (**cmd_line && ft_is_space(**cmd_line))
		(*cmd_line)++;
	if (**cmd_line == '\0')
		return (NULL);
	start = *cmd_line;
	while (**cmd_line && !ft_is_space(**cmd_line))
	{
		(*cmd_line)++;
		len++;
	}
	token = (char *)malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, start, len + 1); // por seguridad devuelve una copia
	return (token);
}*/

/*static int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}*/