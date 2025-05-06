/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:08:41 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/05/06 09:51:32 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <pthread.h>
# include <signal.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"
# include "./structs.h"
# include "./shell.h"
# include "./tokens.h"
# include "src/get_next_line/get_next_line.h"

# define RST	"\033[0m"
# define G		"\033[1;32m"
# define Y		"\033[38;2;252;255;166m"
# define B		"\033[1;34m"
# define M		"\033[1;35m"
# define C		"\033[1;36m"
# define W		"\033[1;37m"
# define S      "\033[38;5;147m"
# define USER_M		"\033[38;2;193;255;215m"
# define BABY_BLUE		"\033[38;2;177;240;247m"

# define T_SQUOTE	'\''
# define T_DQUOTE	'"'
# define T_ESCAPE	'\\'
# define T_PIPE		'|'
# define T_LESS		'<'
# define T_GREATER	'>'
# define T_SMCOLON	';'
# define T_SPACE	' '

# define RED "\033[0;31m"
# define DARK_PINK "\033[38;2;189;30;30m"
# define LIGHT_PINK "\033[38;2;216;131;115m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[1;34m"
# define END "\033[0m"
# define CYAN "\033[1;36m"

void		print_header(void);


#endif
