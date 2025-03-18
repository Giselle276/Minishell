/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-18 12:27:52 by gmaccha-          #+#    #+#             */
/*   Updated: 2025-03-18 12:27:52 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_hash_tab	*load_env(char *envp[])
{
	t_ht_tab	*env;
	int			i;

	i = 0;
	env = create_table((int)HT_SIZE_ENV);
	while (envp[i])
	{
		set_value(env, envp[i], 1);
		i++;
	}
	return (env);
}
