/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudia <claudia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:57:22 by cgil              #+#    #+#             */
/*   Updated: 2025/05/02 14:47:34 by claudia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	builtin_pwd(void)
{
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	perror("pwd");
	return (1);
}

/*int	builtin_export(char **argv, t_status *status)
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
}*/
//perfecta pero muy larga
/*int	builtin_export(char **argv, t_status *status)
{
	int		i;
	char	*sep;
	char	*key;
	char	*value;	

	i = 1;
	if (!argv[1])
	{
		i = 0;
		while (status->envp[i])
		{
			printf("declare -x %s\n", status->envp[i]);
			i++;
		}
		return (0);
	}
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
			status->envp = set_env_value(status->envp, argv[i], "");
		i++;
	}
	return (0);
}*/

// Función para imprimir las variables de entorno precedidas de declare -x
void	print_exported_env(t_status *status)
{
	int	i;

	i = 0;
	while (status->envp[i])
	{
		printf("declare -x %s\n", status->envp[i]);
		i++;
	}
}

// Función para procesar cada argumento y asignar variables de entorno
void	process_export_argument(char *arg, t_status *status)
{
	char	*sep;
	char	*key;
	char	*value;

	sep = ft_strchr(arg, '=');
	if (sep)
	{
		*sep = '\0';
		key = arg;
		value = sep + 1;
		status->envp = set_env_value(status->envp, key, value);
		*sep = '='; // Restaurar la cadena original
	}
	else
		 status->envp = set_env_value(status->envp, arg, ""); // Asignar variable vacía
}

// Función principal para exportar las variables
int	builtin_export(char **argv, t_status *status)
{
	int	i;

	i = 1;
	if (!argv[1])
	{
		print_exported_env(status);
		return (0);
	}
	while (argv[i])
	{
		process_export_argument(argv[i], status);
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

