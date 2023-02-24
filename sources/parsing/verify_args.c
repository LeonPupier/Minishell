/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:28:56 by lpupier           #+#    #+#             */
/*   Updated: 2023/02/24 14:30:23 by lpupier          ###   ########.fr       */
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

static char	*get_var(char *str, char **envp)
{
	int	idx;
	int	is_quote;

	idx = -1;
	is_quote = 0;
	while (str[++idx])
	{
		if (str[idx] == '\'')
			is_quote = !is_quote;
		else if (str[idx] == '$' && !is_quote)
			idx = replace_var(envp, &str, idx + 1, idx + 1);
	}
	return (str);
}

static char	*whitout_c(char *str)
{
	char	*new_str;
	int		idx;
	int		new_idx;
	int		len;

	idx = -1;
	len = 0;
	while (str[++idx])
	{
		if (str[idx] != '"' && str[idx] != '\'')
			len++;
	}
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	idx = -1;
	new_idx = -1;
	while (str[++idx])
	{
		if (str[idx] != '"' && str[idx] != '\'')
			new_str[++new_idx] = str[idx];
	}
	return (free(str), new_str[++new_idx] = '\0', new_str);
}

static int	parse_quotes(char ***cmd, char *str, t_parsing *parsing)
{
	if (str[parsing->idx] == '"' || str[parsing->idx] == '\'')
	{
		parsing->c = str[parsing->idx];
		parsing->idx++;
		while (str[parsing->idx] && str[parsing->idx] != parsing->c)
			parsing->idx++;
		if (!str[parsing->idx])
			return (0);
		while (str[parsing->idx] && str[parsing->idx] != ' ')
			parsing->idx++;
		*cmd = add_to_tab(*cmd, whitout_c(get_var(\
		ft_substr(str, parsing->idx_init, parsing->idx - parsing->idx_init), \
				parsing->envp)));
		parsing->idx_init = parsing->idx;
		return (1);
	}
	return (1);
}

char	**cmd_parsing(char **cmd, char *str, char **envp)
{
	t_parsing	parsing;

	parsing.idx = 0;
	parsing.idx_init = 0;
	parsing.envp = envp;
	while (str[parsing.idx])
	{
		if (str[parsing.idx] == ' ')
		{
			if (str[parsing.idx - 1] != ' ' && parsing.idx_init != parsing.idx)
				cmd = add_to_tab(cmd, get_var(ft_substr(str, parsing.idx_init, \
						parsing.idx - parsing.idx_init), envp));
			parsing.idx++;
			parsing.idx_init = parsing.idx;
			continue ;
		}
		if (!parse_quotes(&cmd, str, &parsing))
			continue ;
		parsing.idx++;
	}
	if (str[parsing.idx - 1] == ' ')
		return (cmd);
	return (cmd = add_to_tab(cmd, get_var(ft_substr(str, parsing.idx_init, \
				parsing.idx - parsing.idx_init), envp)), cmd);
}
