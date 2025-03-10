/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-07 12:08:41 by gmaccha-          #+#    #+#             */
/*   Updated: 2025-03-07 12:08:41 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define RST	"\033[0m"
//# define RED	"\033[1;31m"
# define G		"\033[1;32m"
#define  Y		"\033[38;2;252;255;166m"
# define B		"\033[1;34m"
# define M		"\033[1;35m"
# define C		"\033[1;36m"
# define W		"\033[1;37m"
# define S      "\033[38;5;147m"
#define USER_M		"\033[38;2;193;255;215m"
#define BABY_BLUE		"\033[38;2;177;240;247m"

# define RED "\033[0;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[1;34m"
# define END "\033[0m"
# define CYAN "\033[1;36m"

#define HISTORY_FILE ".minishell_history"

void	print_header(void);

#endif
