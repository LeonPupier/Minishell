/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:47:39 by lpupier           #+#    #+#             */
/*   Updated: 2023/01/19 18:17:59 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sort_envp(char **envp)
{
	int		i;
	int		j;
	int		size;
	char	*temp;
	
	i = 0;
	size = get_array_size(envp);
	while (i < size)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (ft_strncmp(envp[j], envp[j + 1], INT_MAX) > 0)
			{
				temp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = temp;
			}
			j++;
		}
		i++;
	}

}

void	ft_export(char **cmd, char **envp)
{
	int		i;
	char	**new_envp;
	int		argc;
	
	i = 0;
	argc = get_array_size(cmd);
	if (argc == 1)
	{
		sort_envp(envp);
		while (envp[i])
		{
			if (ft_strncmp(envp[i], "_=", 2) != 0)
				printf("%s\n", envp[i]);
			i++;
		}
	}
	else if (argc == 2)
	{
		new_envp = malloc(sizeof(char *) * (argc + 1));
		if (!new_envp)
			return ;
		while (envp[i])
		{
			new_envp[i] = envp[i];
			i++;
		}
		new_envp[i] = cmd[1];
		envp = new_envp;
	}
}