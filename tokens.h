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

/*typedef enum e_token_type // tipo de token
{
	TEXT,
	BUILTIN,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND, // >> -> si no existe lo crea y si existe lo agrega al final
	HEREDOC,
	SEMICOLON,
	TOKEN_END
}			t_token_type;

typedef struct s_token // clasificacion de los tokens
{
	char 			*value;
	t_token_type 	type;
    struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_positions
{
	size_t	i;
	size_t	j;
	size_t	k;
	int		len;
	char	*stemp;
}	t_positions;*/

void	tokenizing(t_cmds *ct);
// error
#endif