#include "../../shell.h"

void	print_pipes_only(t_token *lst)
{
	while (lst)
	{
		if (lst->type == T_PIPE)
			printf("Found PIPE token: '%s'\n", lst->value);
		lst = lst->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	t_token	*tmp;

	printf("Args:\n");
	tmp = cmd->args;
	while (tmp)
	{
		printf("  %s\n", tmp->value);
		tmp = tmp->next;
	}
	printf("Redir In:\n");
	tmp = cmd->redir_in;
	while (tmp)
	{
		printf("  %s\n", tmp->value);
		tmp = tmp->next;
	}

	printf("Redir Out:\n");
	tmp = cmd->redir_out;
	while (tmp)
	{
		printf("  %s\n", tmp->value);
		tmp = tmp->next;
	}
}

void	print_tokens(t_token *token_lst)
{
	while (token_lst)
	{
		printf("Token: %s Type: %d\n", token_lst->value, token_lst->type);
		token_lst = token_lst->next;
	}
}

void	print_piped_cmds(t_token **piped_cmds)
{
    int	i;

	i = 0;
	while (piped_cmds[i])
	{
		printf("Piped Command %d:\n", i + 1);
		print_tokens(piped_cmds[i]);
		i++;
	}
}

void	print_token_list(t_token *lst)
{
	while (lst)
	{
		printf("Token: '%s' Type: %d\n", lst->value, lst->type);
		lst = lst->next;
	}
}

void	print_all_parsed_cmds(t_cmd **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		printf("\n🧩 Comando %d:\n", i + 1);
		print_cmd(cmds[i]);
		i++;
	}
}