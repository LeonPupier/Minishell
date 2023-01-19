/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:26:01 by lpupier           #+#    #+#             */
/*   Updated: 2023/01/19 18:18:17 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tab(char **tab)
{
	int	idx;

	idx = 0;
	while (tab[idx])
	{
		free(tab[idx]);
		idx++;
	}
	free(tab);
}

int		get_array_size(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

char	**replace_var(char **cmd)
{
	int		count;
	int		idx;
	int		new_idx;
	char	*var;

	count = 0;
	while (cmd[count])
	{
		idx = 0;
		while (cmd[count][idx])
		{
			if (cmd[count][idx] == '$')
			{
				idx++;
				new_idx = idx;
				while (cmd[count][new_idx] && ft_isalpha(cmd[count][new_idx]))
					new_idx++;
				var = ft_substr(cmd[count], idx, new_idx - 1);
				if (getenv(var))
					cmd[count] = ft_strdup(getenv(var));
				free(var);
				idx = new_idx;
				continue ;
			}
			idx++;
		}
		count++;
	}
	return (cmd);
}
