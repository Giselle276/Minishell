/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:21:25 by cgil              #+#    #+#             */
/*   Updated: 2025/04/10 20:01:42 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../tokens.h"

static char update_quote(char quote, char c);

/*int	check_only_char(char *str, char look)
{
	while (*str)
	{
		if (*str != look)
			return (1); // habia un caracter distinto
		str++;
	}
	return (0); // solo habia look
}

/*int	validate_piped_cmd(char *line)
{
	char	*pipe;

	if (!ft_strchr(line, T_PIPE))
		return (0);
	pipe = ft_strchr(line, T_PIPE); // posicion del primer pipe
	if (ft_strlen(pipe) <= 1) // ver si el pipe es el ultimo caracter // que deberia hacer
		return (0);
	if ((*(pipe + 2) == '|' || *(pipe  + 1) == '|' || !check_only_char(pipe + 1, ' ')))
		return (0);
	return (1);
}

void	tokenizing(t_cmds *ct)
{
	//if (validate_piped_cmd(ct->cmd_line))
		//ct->piped_cmd = piped_cmd(ct->cmd_line);
	//else 
	ct->not_piped_cmd = split_tk(ct->cmd_line, T_SPACE, ct);
	return ; 
}

t_token	*split_tk(char *cmd, char delimiter, t_cmds *ct)
{
	t_token	*head;
	char	*tmp;

	tmp = clean_line(cmd, ct); // to do
	if (tmp == NULL)
		return (NULL);
	ct->cmd_splitted = alocate_matrix(tmp, delimiter); // to do
	if (ct->cmd_splitted == NULL)
		validate_error(EALLOC, "Error while allocating memory", NULL);
	ct->cmd_splitted = split_cmd(tmp, delimiter, ct); // to do
	head = make_tokens(ct, ct->cmd_splitted); // to do
	free(tmp);
	return (head);
}

// limpiar espacios y chequear sintax

char *clean_line(char *line, t_cmds *ct)
{
	char	*cleaned_line;
	char	*tmp;

	ct->status->error_code = 
}*/

t_token_type get_token_type(char *str)
{
	if (!str)
		return (TEXT);
	if (ft_strncmp(str, "|", 2) == 0)
		return (PIPE);
	if (ft_strncmp(str, "<", 2) == 0)
		return (REDIR_IN);
	if (ft_strncmp(str, ">", 2) == 0)
		return (REDIR_OUT);
	if (ft_strncmp(str, "<<", 3) == 0)
		return (APPEND);
	if (ft_strncmp(str, ">>", 3) == 0)
		return (HEREDOC);
	return (TEXT);
}

t_token	*alloc_token(char *value)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->type = get_token_type(value);
	new->next = NULL;
	return (new);
}

t_token	*make_tokens(t_cmds *ct, char **args)
{
	(void)ct; // ??
	t_token	*head;
	t_token	*current;
	t_token	*new;
	int		i;

	i = 0;
	head = NULL;
	current = NULL;
	while (args[i])
	{
		new = alloc_token(args[i]);
		if (!new)
			return (NULL);
		if (!head)
			head = new;
		else
			current->next = new;
		current = new;
		i++;
	}
	return (head);
}

char	**split_by_space(char *line)
{
	char	**args;
	char	quote;
	int		i;
	int  	start;
	int  	count;
	int  	end;
	int	 	len;

	i = 0;
	count = 0;
	start = 0;
	quote = 0;
	end = 0;
	len = 0;

	if (!line)
		return (NULL);
	args = malloc(sizeof(char *)* (ft_strlen(line) + 1));
	if (!args)
		return (NULL);
	while (line[i])
	{	quote = update_quote_state(quote, line[i]); // dentro o fuera de comillas
		if ((line[i] == ' ' && quote == 0) || line[i + 1] == '\0')
		{	// cortar el token
			if (line[i] == ' ')
				end = i;
			else
				end = i + 1; // incluir ultimo caracter
			len = end - start; // longitud total del token
			if (len > 0)
			{
				args[count] = ft_substr(line, start, len); /// copio la linea
				if (!args[count])
					return (NULL);
				count++;
			}
			start = i + 1;
		}
		i++;
	}
	args[count] = NULL;
	return (args);
}

void	tokenizing(t_cmds *ct)
{
	char **args;
	int		i;

	i = 0;
	if (!ct || !ct->cmd_line || ct->cmd_line[0] == '\0')
		return ;
	args = split_by_space(ct->cmd_line); // falta
	if (!args)
	{
		ct->status->error_code = 1;
		return ;
	}
	ct->token_lst = make_tokens(ct, args); // falta
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

char update_quote(char quote, char c) // solo cierra al ser iguales
{
	if ((c == '\'' || c == '\"') && quote == 0)
		return (c); // abre comilla
	else if (c == quote)
		return (0); // si es ' '
	return (quote);
}