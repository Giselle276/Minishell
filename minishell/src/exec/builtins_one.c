/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:39:39 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/04/22 10:48:11 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_cd(char **args, t_status *status)
{
	char	*home;

	home = get_env_value(status->envp, "HOME");
	if (!args[1] && home)
		return (chdir(home));
	if (chdir(args[1]) != 0)
	{
		printf("De aqui viene el error\n");
		//perror("cd");
		status->stat = 1;
		return (1);
	}
	return (0);
}
/*
int	builtin_echo(char **argv)
{
	int i = 1;
	int newline = 1;

	if (argv[i] && strcmp(argv[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}

	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");

	return (0);
}
*/

int	builtin_echo(char **argv)
{
	int i = 1;
	int newline = 1;

	// Verificar si el primer argumento es '-n' para evitar el salto de línea
	if (argv[i] && strcmp(argv[i], "-n") == 0)
	{
		newline = 0;
		i++; // Saltar el '-n'
	}
	// Imprimir los argumentos con espacio entre ellos
	while (argv[i])
	{
		// Imprimir el argumento sin salto de línea
		write(1, argv[i], strlen(argv[i]));
		
		// Si no es el último argumento, agregar un espacio
		if (argv[i + 1])
			write(1, " ", 1);

		i++;
	}
	// Si no se pasó '-n', agregar un salto de línea al final
	if (newline)
		write(1, "\n", 1);

	return (0);
}

int	builtin_exit(char **argv)
{
	int	code;

	code = 0;
	if (argv[1])
		code = ft_atoi(argv[1]);
	exit(code);
}

int	builtin_env(t_status *status)
{
	int	i = 0;

	printf(">> Entrando a builtin_env()\n");
	if (!status->envp || !status->envp[0])
	{
		write(2, "env: environment not set\n", 26);
		return (1);
	}
	while (status->envp[i])
	{
		if (ft_strchr(status->envp[i], '=')) // solo imprime si hay '='
			printf("%s\n", status->envp[i]);
		i++;
	}
	return (0);
}

char	**load_env(char **envp)
{
	char	**copy;
	int		count;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[count] = NULL;
	return (copy);
}
