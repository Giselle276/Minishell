/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:39:39 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/04/16 13:50:55 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int builtin_cd(char **args, t_status *status)
{
	if (!args[1])
		return chdir(getenv("HOME"));
	if (chdir(args[1]) != 0)
	{
		perror("cd");
		status->stat = 1;
		return 1;
	}
	return 0;
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
	int	code = 0;

	if (argv[1])
		code = ft_atoi(argv[1]);
	exit(code);
}

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
int	builtin_env(char **envp)
{
	int	i = 0;

  if (!envp)
  {
        fprintf(stderr, "envp is NULL\n");
        return 1;
    } 
	if (!envp[0]) {
        fprintf(stderr, "envp[0] is NULL\n");
        return 1;
    }

	while (envp[i]!= NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

char **load_env(char **envp)
{
	int count = 0;
	while (envp[count])
		count++;

	char **copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return NULL;

	for (int i = 0; i < count; i++)
		copy[i] = strdup(envp[i]);
	copy[count] = NULL;

	return copy;
}