/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:28:56 by lpupier           #+#    #+#             */
/*   Updated: 2023/02/07 20:40:53 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	replace_var(char **envp, char **cmd, int idx)
{
	char	*var;
	char	*var_env;
	char	*new_cmd;
	int		new_idx;

	if ((*cmd)[idx] == '$')
	{
		idx++;
		new_idx = idx;
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
	return (idx);
}

char	**find_occurrence(char **cmd, char *command, char c)
{
	int		len;
	int		idx;
	int		start;
	int		idx_init;

	len = ft_strlen(command);
	idx = 0;
	while (idx < len)
	{
		idx_init = idx;
		while (command[idx] && command[idx] != c)
			idx++;
		if (idx > len)
			break ;
		cmd = add_to_tab(cmd, ft_split(\
		ft_substr(command, idx_init, idx - idx_init), ' '), NULL);
		idx++;
		start = idx;
		while (command[idx] && command[idx] != c)
			idx++;
		if (idx > len)
			break ;
		cmd = add_to_tab(cmd, NULL, ft_substr(command, start, idx - start));
		idx++;
	}

	//int i = -1;
	//while (cmd[++i])
	//	printf("%d:	[%s]\n", i, cmd[i]);
	
	return (cmd);
}

char	**verify_args(char **cmd, char **envp)
{
	int		count;
	int		idx;

	count = -1;
	while (cmd[++count])
	{
		idx = -1;
		while (cmd[count][++idx])
		{
			idx = replace_var(envp, &cmd[count], idx);
		}
	}
	return (cmd);
}
