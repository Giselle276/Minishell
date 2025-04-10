/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:18:26 by claudia           #+#    #+#             */
/*   Updated: 2025/04/10 20:01:25 by claudia          ###   ########.fr       */
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
t_token_type get_token_type(char *str);
t_token	*alloc_token(char *value);
t_token	*make_tokens(t_cmds *ct, char **args);
char	**split_by_space(char *line);

// error
#endif