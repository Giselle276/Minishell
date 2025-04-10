/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:18:26 by claudia           #+#    #+#             */
/*   Updated: 2025/04/05 17:04:46 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "./minishell.h"

typedef struct s_positions
{
	size_t	i;
	size_t	j;
	size_t	k;
	int		len;
	char	*stemp;
}	t_positions;

void	tokenizing(t_cmds *ct);
int		validate_piped_cmd(char *line);


// error
#endif