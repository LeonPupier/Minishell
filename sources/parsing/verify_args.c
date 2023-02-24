/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:28:56 by lpupier           #+#    #+#             */
/*   Updated: 2023/02/22 19:40:10 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	replace_var(char **envp, char **cmd, int idx, int new_idx)
{
	char	*var;
	char	*var_env;
	char	*new_cmd;

	while ((*cmd)[new_idx] && \
	(ft_isalnum((*cmd)[new_idx]) || (*cmd)[new_idx] == '_'))
		new_idx++;
	var = ft_substr(*cmd, idx, new_idx - idx);
	var_env = get_env(envp, var);
	free(var);
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
			new_cmd = ft_strjoin(ft_substr(*cmd, 0, idx - 1), \
			ft_substr(*cmd, new_idx, ft_strlen(*cmd)));
	}
	return (free(*cmd), *cmd = new_cmd, new_idx);
}

static char	*retrieve_environment_variables(char *str, char **envp)
{
	int		idx;

	idx = -1;
	while (str[++idx])
	{
		if (str[idx] == '$')
			idx = replace_var(envp, &str, idx + 1, idx + 1);
	}
	return (str);
}

static char	*whitout_c(char *str, char c)
{
	char	*new_str;
	int		idx;
	int		new_idx;
	int		len;

	idx = -1;
	len = 0;
	while (str[++idx])
	{
		if (str[idx] != c)
			len++;
	}
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	idx = -1;
	new_idx = -1;
	while (str[++idx])
	{
		if (str[idx] != c)
			new_str[++new_idx] = str[idx];
	}
	return (free(str), new_str[++new_idx] = '\0', new_str);
}

char	**parsing(char **cmd, char *str, char **envp)
{
	char	c;
	int		idx;
	int		idx_init;

	c = 0;
	idx = 0;
	idx_init = 0;
	while (str[idx])
	{
		if (str[idx] == ' ')
		{
			if (str[idx - 1] != ' ' && idx_init != idx)
				cmd = add_to_tab(cmd, retrieve_environment_variables(\
						ft_substr(str, idx_init, idx - idx_init), envp));
			idx++;
			idx_init = idx;
			continue ;
		}
		else if (str[idx] == '"' || str[idx] == '\'')
		{
			c = str[idx];
			idx++;
			while (str[idx] && str[idx] != c)
				idx++;
			if (!str[idx])
				continue ;
			while (str[idx] && str[idx] != ' ')
				idx++;
			if (c == '"')
				cmd = add_to_tab(cmd, whitout_c(retrieve_environment_variables(\
				ft_substr(str, idx_init, idx - idx_init), envp), c));
			else
				cmd = add_to_tab(cmd, whitout_c(ft_substr(str, idx_init, \
				idx - idx_init), c));
			idx_init = idx;
			continue ;
		}
		idx++;
	}
	if (str[idx - 1] == ' ')
		return (cmd);
	return (cmd = add_to_tab(cmd, retrieve_environment_variables(\
			ft_substr(str, idx_init, idx - idx_init), envp)), cmd);
}
