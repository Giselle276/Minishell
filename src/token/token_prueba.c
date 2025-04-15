/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_prueba.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:39:05 by claudia           #+#    #+#             */
/*   Updated: 2025/04/15 11:13:21 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*void	tokenizing(t_cmds *ct)
{
	t_token	*tkn_list;

	tkn_list = tokenize_line(ct->cmd_line);
	ct->token_lst = tkn_list;

	if (!tkn_list)
		return ;
	if (has_pipe(tkn_list))
		ct->piped_cmd = handle_piped_cmd(tkn_list);
	else
		ct->not_piped_cmd = handle_simple_cmd(tkn_list);
}

char	update_quote(char quote, char c) // solo cierra al ser iguales
{
	if ((c == '\'' || c == '\"') && quote == 0)
		return (c); // abre comilla
	else if (c == quote)
		return (0); // si es ' '
	else if (c == '\\')
		return (quote);
	return (quote);
}

t_token	*tokenize_line(char *cmd_line)
{
	t_token	*token_lst;
	char	*token_str;
	int		i;

	i = 0;
	while (cmd_line[i])
	{
		token_str = get_next_token(cmd_line, &i);
		if (!token_str)
		{
			// manejar error de comillas no cerradas
			return (NULL);
		}
		add_token(&token_lst, create_token(token_str)); // define tipo en create_token
		free(token_str);
	}
	return (token_lst);
}*/
// obtiene token por token revisando el estado de las comillas
char	*get_token(char *line, int *i)
{
	int		start;
	char	qt;

	start = 0;
	qt = 0;
	while(line[*i] && line[*i] == ' ')
		(*i)++;
	start = *i;
	while (line[*i])
	{
		qt = update_quote(qt, line[*i]);
		if (!qt && line[*i] == ' ')
			break; //cortar token
		(*i)++;
	}
	if (qt)
		return (NULL); // comillas no cerradas
	return (ft_substr(line, start, *i -start)); // retorna tokens cortados 
}
char	update_quote(char quote, char c) // solo cierra al ser iguales
{
	if ((c == '\'' || c == '\"') && quote == 0)
		return (c); // abre comilla
	else if (c == quote)
		return (0); // si es ' '
	/*else if (c == '\\')
		return (quote);*/
	return (quote);
}

// dirige a que se obtenga el token, se le asigne memoria y se incluya a la lista
t_token	*tokenize_line(char *cmd_line)
{
	t_token *tk_lst;
	char	*tk_str;
	int		i;

	i = 0;
	tk_lst = NULL;
	while (cmd_line[i])
	{
		tk_str = get_token(cmd_line, &i);
		printf("DEBUG token string: '%s'\n", tk_str);
		if (!tk_str)
		{
			free_tokens(tk_lst);
			return (NULL);
		}
		add_token(&tk_lst, create_token(tk_str));
		free(tk_str);
	}
	return (tk_lst);
}

void print_tokens(t_token *token_lst)
{
    while (token_lst)
    {
        printf("Token: %s Type: %d\n", token_lst->value, token_lst->type);
        token_lst = token_lst->next;
    }
}

void print_piped_cmds(t_token **piped_cmds)
{
    int i = 0;

    while (piped_cmds[i])  // Recorrer cada grupo de comandos
    {
        printf("Piped Command %d:\n", i + 1);
        print_tokens(piped_cmds[i]);  // Imprime los tokens de cada comando
        i++;
    }
}

void print_token_list(t_token *lst)
{
	while (lst)
	{
		printf("Token: '%s' Type: %d\n", lst->value, lst->type);
		lst = lst->next;
	}
}

void	tokenizing(t_cmds *ct)
{
	ct->token_lst = tokenize_line(ct->cmd_line);
	print_token_list(ct->token_lst);
	if (!ct->token_lst)
		return ;
	//print_tokens(ct->token_lst);
	if (has_pipe(ct->token_lst))
	{
		ct->piped_cmd = group_piped_cmd(ct->token_lst);
		print_piped_cmds(ct->piped_cmd);
	}
	else
		printf("COMANDO SIMPLE NO HAGO NADA AUN\n");
		//ct->not_piped_cmd = handle_simple_cmd(ct->token_lst); // ver
}