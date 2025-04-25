/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgil <cgil@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:57:22 by cgil              #+#    #+#             */
/*   Updated: 2025/04/23 19:19:36 by cgil             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	builtin_pwd(void)
{
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return 0;
	}
	perror("pwd");
	return 1;
}

int	builtin_export(char **argv, t_status *status)
{
	int		i;
	char	*sep;
	char	*key;
	char	*value;

	if (!argv[1])
		return (builtin_env(argv, status)); // Mostrar todas si no hay args

	i = 1;
	while (argv[i])
	{
		sep = ft_strchr(argv[i], '=');
		if (sep)
		{
			*sep = '\0';
			key = argv[i];
			value = sep + 1;
			status->envp = set_env_value(status->envp, key, value);
			*sep = '='; // Restaurar la cadena original
		}
		else
			status->envp = set_env_value(status->envp, argv[i], ""); // Asignar variable vacía
		i++;
	}
	return (0);
}

int	builtin_unset(char **argv, t_status *status)
{
	int	i;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		status->envp = unset_env_value(status->envp, argv[i]);
		i++;
	}
	return (0);
}

