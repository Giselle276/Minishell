/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:21:25 by cgil              #+#    #+#             */
/*   Updated: 2025/04/12 14:32:15 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../tokens.h"

static	char	update_quote(char quote, char c);

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

int	validate_piped_cmd(char *line)
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

t_token_type	get_token_type(char *str)
{
	if (!str)
		return (TEXT);
	if (ft_strncmp(str, "|", 2) == 0)
	{
		  printf("Token '%s' es de tipo PIPE\n", str);  // Depuración
		  return (PIPE);
	}
		
	if (ft_strncmp(str, "<", 2) == 0)
		return (REDIR_IN);
	if (ft_strncmp(str, ">", 2) == 0)
		return (REDIR_OUT);
	if (ft_strncmp(str, "<<", 3) == 0)
		return (APPEND);
	if (ft_strncmp(str, ">>", 3) == 0)
		return (HEREDOC);
	printf("Token '%s' es de tipo TEXT\n", str);
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

t_token	*make_tokens(t_cmds *ct, char **cmds)
{
	t_token	*head;
	t_token	*current;
	t_token	*new;
	int		i;

	i = 0;
	head = NULL;
	current = NULL;
	if (!cmds)
		return (NULL);
	while (cmds[i])
	{
		new = alloc_token(cmds[i]);
		if (!new)
			return (NULL);
		if (!head)
			head = new;
		else
			current->next = new;
		current = new;
		i++;
	}
	ct->token_lst = head;
	return (head);
}

char	**split_by_space(char *line)
{
	char	**args;
	char	quote;
	int		i;
	int		start;
	int		count;
	int		end;
	int		len;
	int		j;

	i = 0;
	j = 0;
	count = 0;
	start = 0;
	quote = 0;
	end = 0;
	len = 0;

	if (!line)
		return (NULL);
	args = malloc(sizeof(char *) * (ft_strlen(line) + 1));
	if (!args)
	{
		return (NULL);
	}
	while (line[i])
	{
		quote = update_quote(quote, line[i]); // dentro o fuera de comillas
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
				{
					while (j < count)
					{
						free(args[j]);
						j++;
					}
					free(args);
					return (NULL);
				}
				count++;
			}
			start = i + 1;
		}
		i++;
	}
	args[count] = NULL;
	return (args);
}

t_token	**split_by_pipe(char *line)
{
	int		i;
	int		cmd_count;
	int		start;
	int		cmd_index;
	int		quote;
	t_token	**piped_cmds;

	i = 0;
	cmd_count = 1;
	if (!line)
		return (NULL);
	// Contar cuántos pipes hay
	while (line[i])
	{
		quote = update_quote(quote, line[i]);
		if (line[i] == '|' && quote == 0)
			cmd_count++;
		i++;
	}
	 piped_cmds = malloc(sizeof(t_token *) * (cmd_count + 1));
	if (!piped_cmds)
		return (NULL);

	// Separar la línea en comandos usando el pipe
	i = 0;
	cmd_index = 0;
	start = 0;
	quote = 0;
	while (line[i])
	{
		quote = update_quote(quote, line[i]);
		if (line[i] == '|' && quote == 0)
		{
			piped_cmds[cmd_index] = make_token_for_pipe(line, start, i);  // Creamos un token para el comando anterior
			start = i + 1;
			cmd_index++;
		}
		i++;
	}
	  // Añadimos el último comando después del último pipe
	piped_cmds[cmd_index] = make_token_for_pipe(line, start, i);
	piped_cmds[cmd_index + 1] = NULL;  // Terminamos con NULL
	return (piped_cmds);
}

void	tokenizing(t_cmds *ct)
{
	char	**args;
	int		i;
	int		j;
	int		pipe_count;

	i = 0;
	j = 0;
	if (!ct || !ct->cmd_line || ct->cmd_line[0] == '\0')
	{
		
	   //printf("Tokenizing: %s\n", ct->cmd_line); // para prueba
	   return ;
	}
	ct->piped_cmd = split_by_pipe(ct->cmd_line); // falta
	if (!ct->piped_cmd)
	{
		ct->status->error_code = 1;
		return ;
	}
	// Reservar espacio para los tokens de cada comando separado por pipe
	pipe_count = get_pipe_count(ct->cmd_line);
	//ct->piped_cmd = malloc(sizeof(t_token*) * (pipe_count + 1));
	if (!ct->piped_cmd)
	{
		ct->status->error_code = 1;
		return ;
	}
	if (pipe_count == 0)
	{
		args = split_by_space(ct->cmd_line);
		if (!args)
		{
			ct->status->error_code = 1;
			return ;
		}
		ct->piped_cmd[0] = make_tokens(ct, args);  // Aquí almacenamos los tokens del único comando
		ct->piped_cmd[1] = NULL;  // Terminamos el arreglo de comandos piped
		while (args[j])
		{
			free(args[j]);
			j++;
		}
		free (args);
	}
	else
	{
		while (ct->piped_cmd[i])
		{
			args = split_by_space(ct->piped_cmd[i]->value);
			if (!args)
			{
				ct->status->error_code = 1;
				return ;
			}
		/*// 🧪 DEBUG
			printf("Comando separado: %s\n", cmds[i]);
			int k = 0;
			while (args[k])
			{
				printf(" - Token: %s\n", args[k]);
				k++;
			}
		// 🧪 FIN DEBUG	
		*/
		
			//ct->token_lst = make_tokens(ct, args); // falta
			ct->piped_cmd[i] = make_tokens(ct, args);
			while (args[j])
			{
				free(args[j]);
				j++;
			}
			free(args);
			i++;
		}
		ct->piped_cmd[i] = NULL;
	}
	print_tokens(ct->piped_cmd);

}
/*
void	tokenizing(t_cmds *ct)
{
	char	**args;
	char	**cmds;
	int		i;

	i = 0;
	if (!ct || !ct->cmd_line || ct->cmd_line[0] == '\0')
		return ;
	   //printf("Tokenizing: %s\n", ct->cmd_line); // para prueba
	args = split_by_space(ct->cmd_line); // falta
	if (!args)
	{
		ct->status->error_code = 1;
		return ;
	}
	ct->token_lst = make_tokens(ct, args); // falta
	while (args[i])
	{
		// printf("Token[%d]: %s\n", i, args[i]);//para prueba
		free(args[i]);
		i++;
	}
	free(args);
}
*/

char update_quote(char quote, char c) // solo cierra al ser iguales
{
	if ((c == '\'' || c == '\"') && quote == 0)
		return (c); // abre comilla
	else if (c == quote)
		return (0); // si es ' '
	else if (c == '\\')
		return (quote);
	return (quote);
}


int get_pipe_count(char *line)
{
	int		count = 0;
	int		i = 0;
	int		quote = 0;
	
	while	(line[i])
	{
		quote = update_quote(quote, line[i]);
		if (line[i] == '|' && quote == 0)
			count++;
		i++;
	}
	return (count);
}

void print_tokens(t_token **piped_cmds)
{
	int i = 0;
	while (piped_cmds[i])
	{
		t_token *current = piped_cmds[i];
		printf("Comando %d:\n", i + 1);  // Imprimir qué comando estamos procesando
		while (current)
		{
			printf(" - Token: %s (Tipo: %d)\n", current->value, current->type);
			current = current->next;
		}
		i++;
	}
}

t_token *make_token_for_pipe(char *line, int start, int end)
{
	char *sub_str = ft_substr(line, start, end - start);
	t_token *new_token = alloc_token(sub_str);
	free(sub_str);
	return new_token;
}