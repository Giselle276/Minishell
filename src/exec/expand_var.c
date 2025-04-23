/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmaccha- <gmaccha-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:06:18 by gmaccha-          #+#    #+#             */
/*   Updated: 2025/04/23 13:04:45 by gmaccha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_var_value(char *var_start, t_status *status)
{
	char	*var_name;
	char	*value;
	int		var_len;

	if (*var_start == '?')
		return (ft_itoa(status->error_code));
	var_len = 0;
	while (var_start[var_len]
		&& (ft_isalnum(var_start[var_len]) || var_start[var_len] == '_'))
		var_len++;
	var_name = ft_substr(var_start, 0, var_len);
	value = getenv(var_name);
	free(var_name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static char	*extract_suffix(char *str)
{
	int		i;
	char	*suffix;

	i = 0;
	if (*str == '?')
		return (ft_strdup(str + 1));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	suffix = ft_strdup(str + i);
	return (suffix);
}

static char	*get_prefix(const char *str, char *var)
{
	int		len;

	len = var - str;
	return (ft_substr(str, 0, len));
}

static char	*join_parts(char *prefix, char *value, char *suffix)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(prefix, value);
	result = ft_strjoin(tmp, suffix);
	free(prefix);
	free(value);
	free(suffix);
	free(tmp);
	return (result);
}

char	*expand_var(const char *str, t_status *status)
{
	char	*var;
	char	*prefix;
	char	*value;
	char	*suffix;

	var = ft_strchr(str, '$');
	if (!var)
		return (ft_strdup(str));
	prefix = get_prefix(str, var);
	value = get_var_value(var + 1, status);
	suffix = extract_suffix(var + 1);
	return (join_parts(prefix, value, suffix));
}
