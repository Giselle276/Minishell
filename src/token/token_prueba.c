/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_prueba.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:39:05 by claudia           #+#    #+#             */
/*   Updated: 2025/04/15 14:13:45 by gmaccha-         ###   ########.fr       */
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
		if (!tk_str)
		{
			free_tokens(tk_lst);
			return (NULL);
		}
		
		t_token *new_token = create_token(tk_str);
		
		// Verifica si el token es inválido (en este caso si es -1)
		if (new_token->type == T_INVALID) 
		{
			printf("🚫 Token inválido detectado: '%s'\n", tk_str);
			free(tk_str); // Libera el string del token
			free_tokens(tk_lst); // Libera los tokens que ya estaban
			free(new_token); // Libera el token inválido
			return (NULL); // Detiene la tokenización y devuelve NULL
		}
		// Si el token es válido, lo agregamos a la lista
		add_token(&tk_lst, new_token);
		
		
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
	// Paso 1: Tokenizar la línea de comandos
	ct->token_lst = tokenize_line(ct->cmd_line);
	//print_token_list(ct->token_lst);
	print_pipes_only(ct->token_lst); // imprime solo los pipes
	if (!ct->token_lst)
		return ;
	//print_tokens(ct->token_lst);
	
	// Paso 2: Verificación de sintaxis de pipes

	if (!is_valid_pipe_syntax(ct->token_lst))
	{
		printf("🚫 Error de sintaxis con pipes\n");
		free_tokens(ct->token_lst); // libera la memoria
		ct->token_lst = NULL;
		return ;
	}
		// Paso 3: Verifica si hay pipes
	if (has_pipe(ct->token_lst))
	{
		ct->piped_cmd = group_piped_cmd(ct->token_lst);
		print_piped_cmds(ct->piped_cmd);
		ct->parsed_cmds = parse_all_cmds(ct->piped_cmd);
		
		int i = 0;
		while (ct->parsed_cmds && ct->parsed_cmds[i])
		{
			printf("\nParsed Command #%d:\n", i + 1);
			print_cmd(ct->parsed_cmds[i]);
			i++;
		}
	}
	else
	{
		//printf("COMANDO SIMPLE NO HAGO NADA AUN\n");
		//ct->not_piped_cmd = handle_simple_cmd(ct->token_lst); // ver
		ct->parsed_simple = parse_cmd_tokens(ct->token_lst);
		
		printf("\nParsed Simple Command:\n");
		print_cmd(ct->parsed_simple);
	}
}

void print_cmd(t_cmd *cmd)
{
	t_token *tmp;

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

void print_pipes_only(t_token *lst)
{
	while (lst)
	{
		if (lst->type == T_PIPE)
			printf("Found PIPE token: '%s'\n", lst->value);
		lst = lst->next;
	}
}
