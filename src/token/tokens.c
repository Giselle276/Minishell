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

	if (!ft_strchr(line, T_PIPE))
		return (0);
	pipe = ft_strchr(line, T_PIPE); // posicion del primer pipe
	if (ft_strlen(pipe) <= 1) // ver si el pipe es el ultimo caracter
		return (0);
	if ((*(pipe + 2) == '|' || *(pipe  + 1) == '|' || !check_only_char(pipe + 1, ' ')))
		return (0);
	return (1);
}

/*void	tokenizing(t_cmds *ct)
{
	//if (validate_piped_cmd(ct->cmd_line))
		//ct->piped_cmd = piped_cmd(ct->cmd_line);
	//else 
		//ct->not_piped_cmd = split_tk(ct->cmd_line, T_SPACE, ct);
	return ; 
}*/

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
}
