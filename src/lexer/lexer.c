/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:14:00 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/03/25 17:30:20 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*int   check_closed_qt(char *str, char q)
{
    int    single_q;
    int    double_q;
    int    i;

    single_q = 0;
    double_q = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '\'' && !double_q) // si no es doble
            single_q = !single_q;
        else if (str[i] == '\"' && !single_q) // si no es simple
            double_q = !double_q;
        if ((single_q || double_q) && str[i] == q)
            return (1);
        i++;
    }
    return (0);
}*/

