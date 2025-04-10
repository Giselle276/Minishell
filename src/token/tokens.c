/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:21:25 by cgil              #+#    #+#             */
/*   Updated: 2025/04/05 17:39:36 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../tokens.h"

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
		error_code = 1;
		ct->status = error_code;
		return ;
	}
	ct->token_lst = make_tokens(args); // falta
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

char update_quote(char quote, char c) // solo cierra al ser iguales
{
	if ((c == '\'' || c == "\"") && quote == 0)
		return (c); // abre comilla
	else if (c == quote)
		return (0); // si es ' '
	return (quote);
}

char	**split_by_space(char *line)
{
	char *args;
	char  quote;
	int	 i;
	int  start;
	int  count;
	int  end;
	int	 len;

	i = 0;
	count = 0;
	start = 0;
	quote = 0;
	end = 0;
	len = 0;

	if (!line)
		return (NULL);
	args = malloc(sizeof(char *)* ft_strlen(line) + 1);
	if (!args)
		return (NULL);
	while (line[i])
	{	quote = update_quote_state(quote, line[i]);
		if ((line[i] == ' ' && quote == 0) || line[i + 1] == '\0')
		{
			if (line[i] == ' ')
				end = i;
			else
				end = i + 1;
			len = end - start;
		}
	}
}