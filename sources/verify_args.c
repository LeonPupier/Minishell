/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:28:56 by lpupier           #+#    #+#             */
/*   Updated: 2023/01/20 14:32:17 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*replace_var(char *var, char *cmd, int idx, int new_idx)
{
	if (var)
	{
		return (ft_strjoin(ft_strjoin(ft_substr(cmd, 0, idx - 1), var), \
		ft_substr(cmd, new_idx, ft_strlen(cmd))));
	}
	else
		return (ft_strjoin(ft_substr(cmd, 0, idx - 1), \
		ft_substr(cmd, new_idx, ft_strlen(cmd))));
}

char	**verify_args(char **cmd, char **envp)
{
	int		count;
	int		idx;
	int		new_idx;
	char	*var;

	count = -1;
	while (cmd[++count])
	{
		idx = -1;
		while (cmd[count][++idx])
		{
			if (cmd[count][idx] == '$')
			{
				idx++;
				new_idx = idx;
				while (cmd[count][new_idx] && ft_isalnum(cmd[count][new_idx]))
					new_idx++;
				var = ft_substr(cmd[count], idx, new_idx - idx);
				cmd[count] = replace_var(get_env(envp, var), cmd[count], \
				idx, new_idx);
				free(var);
				idx = new_idx;
				continue ;
			}
		}
	}
	return (cmd);
}
