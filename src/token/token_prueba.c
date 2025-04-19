/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_prueba.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:39:05 by claudia           #+#    #+#             */
/*   Updated: 2025/04/19 18:32:28 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// obtiene token por token revisando el estado de las comillas

///////////////////////////printfs/////////////////////////////////////////7

void	print_pipes_only(t_token *lst)
{
	while (lst)
	{
		if (lst->type == T_PIPE)
			printf("Found PIPE token: '%s'\n", lst->value);
		lst = lst->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	t_token	*tmp;

	printf("Args:\n");
	tmp = cmd->args;
	while (tmp)
	{
		printf("  %s\n", tmp->value);
		tmp = tmp->next;
	}
	printf("Redir In:\n");
	tmp = cmd->redir_in;
	while (tmp)
	{
		printf("  %s\n", tmp->value);
		tmp = tmp->next;
	}

	printf("Redir Out:\n");
	tmp = cmd->redir_out;
	while (tmp)
	{
		printf("  %s\n", tmp->value);
		tmp = tmp->next;
	}
}

void	print_tokens(t_token *token_lst)
{
	while (token_lst)
	{
		printf("Token: %s Type: %d\n", token_lst->value, token_lst->type);
		token_lst = token_lst->next;
	}
}

void	print_piped_cmds(t_token **piped_cmds)
{
    int	i;

	i = 0;
	while (piped_cmds[i])  // Recorrer cada grupo de comandos
	{
		printf("Piped Command %d:\n", i + 1);
		print_tokens(piped_cmds[i]);// Imprime los tokens de cada comando
		i++;
	}
}

void	print_token_list(t_token *lst)
{
	while (lst)
	{
		printf("Token: '%s' Type: %d\n", lst->value, lst->type);
		lst = lst->next;
	}
}

void	print_all_parsed_cmds(t_cmd **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		printf("\n🧩 Comando %d:\n", i + 1);
		print_cmd(cmds[i]);
		i++;
	}
}

char	*get_token(char *line, int *i)
{
	int		start;
	char	qt;

	start = 0;
	qt = 0;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	start = *i;
	while (line[*i])
	{
		qt = update_quote(qt, line[*i]);
		if (!qt && line[*i] == ' ')
			break ;
		(*i)++;
	}
	if (qt)
		return (NULL); // comillas no cerradas
	return (ft_substr(line, start, *i - start)); // retorna tokens cortados 
}

char	update_quote(char quote, char c) // solo cierra al ser iguales
{
	if ((c == '\'' || c == '\"') && quote == 0)
		return (c); // abre comilla
	else if (c == quote)
		return (0); // si es ' '
	return (quote);
}

// dirige a que se obtenga el token, se le asigne memoria y se incluya a la lista

t_token	*tokenize_line(char *cmd_line)
{
	t_token	*tk_lst;
	t_token	*new_token;
	char	*tk_str;
	int		i;

	i = 0;
	tk_lst = NULL;
	while (cmd_line[i])
	{
		tk_str = get_token(cmd_line, &i);
		if (!tk_str)
		{
			free_tokens(tk_lst);
			return (NULL);
		}
		new_token = create_token(tk_str);
		if (new_token->type == T_INVALID)
		{
			printf("🚫 Token inválido detectado: '%s'\n", tk_str);
			free(tk_str); // Libera el string del token
			free_tokens(tk_lst); // Libera los tokens que ya estaban
			free(new_token); // Libera el token inválido
			return (NULL); // Detiene la tokenización y devuelve NULL
		}
		add_token(&tk_lst, new_token);
		free(tk_str);
	}
	return (tk_lst);
}

void	tokenizing(t_cmds *ct)
{
	ct->token_lst = tokenize_line(ct->cmd_line);
	if (!ct->token_lst)
		return ;
	if (!is_valid_pipe_syntax(ct->token_lst))
	{
		printf("🚫 Error de sintaxis con pipes\n");
		free_tokens(ct->token_lst);
		ct->token_lst = NULL;
		return ;
	}
}
