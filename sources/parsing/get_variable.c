/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:13:47 by lpupier           #+#    #+#             */
/*   Updated: 2023/03/13 16:39:41 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_var_init(char **envp, char **cmd, int idx, int new_idx)
{
	char	*var;
	char	*var_env;

	while ((*cmd)[new_idx] && \
	(ft_isalnum((*cmd)[new_idx]) || (*cmd)[new_idx] == '_'))
		new_idx++;
	var = ft_substr(*cmd, idx, new_idx - idx);
	var_env = get_env(envp, var);
	free(var);
	return (var_env);
}

char	*get_var(char *str, char **envp)
{
	int		idx;
	int		is_quote;
	char	caracter;

	idx = -1;
	is_quote = 0;
	caracter = 0;
	while (str[++idx])
	{
		if ((str[idx] == '"' || str[idx] == '\'') && caracter == 0)
			caracter = str[idx];
		if (str[idx] == '\'' && caracter == '\'')
			is_quote = !is_quote;
		if (str[idx] == caracter)
			caracter = 0;
		if (str[idx] == '$' && is_quote == 0)
		{
			idx = replace_var(envp, &str, idx + 1, idx + 1) - 1;
			if (idx >= (int)ft_strlen(str))
				break ;
		}
	}
	return (str);
}

int	replace_var(char **envp, char **cmd, int idx, int new_idx)
{
	char	*var_env;
	char	*new_cmd;

	var_env = get_var_init(envp, cmd, idx, new_idx);
	if (var_env)
		new_cmd = ft_strjoin(ft_strjoin(ft_substr(*cmd, 0, idx - 1), \
		var_env), ft_substr(*cmd, new_idx, ft_strlen(*cmd)));
	else
	{
		if (ft_isdigit((*cmd)[idx]))
			new_cmd = ft_strjoin(ft_strjoin(ft_substr(*cmd, 0, idx - 1), \
			ft_substr(*cmd, idx + 1, new_idx)), \
			ft_substr(*cmd, new_idx, ft_strlen(*cmd)));
		else
		{
			new_cmd = ft_strjoin(ft_substr(*cmd, 0, idx - 1), \
			ft_substr(*cmd, new_idx, ft_strlen(*cmd)));
			new_idx = idx - 2;
			if (new_idx < 0)
				new_idx = 0;
		}
	}
	return (free(*cmd), *cmd = new_cmd, new_idx);
}
