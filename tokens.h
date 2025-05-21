/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:18:26 by claudia           #+#    #+#             */
/*   Updated: 2025/05/21 13:05:33 by gmaccha-         ###   ########.fr       */
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

char			update_quote(char quote, char c);
t_token			*handle_tokens(t_cmd *cmd, t_token *tmp);
void			tokenizing(t_cmds *ct, t_status *status);
t_token_type	get_token_type(char *str);
t_token			*create_token(char *str);
void			add_token(t_token **tk_list, t_token *new_token);
t_token			*create_and_validate_tk(char *tk_str, t_status *status);
bool			has_pipe(t_token *lst);
int				count_pipes(t_token *lst);
t_token			**group_piped_cmd(t_token *token_lst);
void			parser(t_cmds *ct);
t_token			*tokenize_line(char *cmd_line, t_status *status);
t_token			*process_tokens(char *cmd_line, t_status *status);
t_token			*create_and_add_token(char *cmd_line, int *i, t_status *status,
					t_token **tk_lst);
char			*join_adjacent_quoted(char *line, int *i, char *quote_type);
int				is_valid_redirection_syntax(t_token *tokens);
int				is_redirection(t_token_type type);
bool			is_valid_pipe_syntax(t_token *lst);

#endif