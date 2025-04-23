/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:18:26 by claudia           #+#    #+#             */
/*   Updated: 2025/04/23 18:34:39 by cgil             ###   ########.fr       */
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

char			*get_token(char *line, int *i);
char			update_quote(char quote, char c);
t_token			*tokenize_line(char *cmd_line);
void			print_tokens(t_token *token_lst);
void			print_piped_cmds(t_token **piped_cmds);
void			tokenizing(t_cmds *ct);
t_token_type	get_token_type(char *str);
t_token			*create_token(char *str);
void			add_token(t_token **tk_list, t_token *new_token);
//void			free_tokens(t_token *list);
t_token			*create_and_validate_tk(char *tk_str);
int				missmatched_quotes(char *str);
bool			has_pipe(t_token *lst);
int				count_pipes(t_token *lst);
t_token			**group_piped_cmd(t_token *token_lst);
void			parser(t_cmds *ct);
void			print_piped_cmds(t_token **piped_cmds);
void			print_all_parsed_cmds(t_cmd **cmds);
// error
#endif