/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:47:39 by lpupier           #+#    #+#             */
/*   Updated: 2023/01/20 16:13:20 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_str_index(char **envp, char *str)
{
	int	i;
	char **cmd_split;
	char **env_split;
	
	i = 0;
	cmd_split = ft_split(str, '=');
	while(envp[i])
	{
		env_split = ft_split(envp[i],'=');
		if (ft_strlen(cmd_split[0]) > ft_strlen(env_split[0]))
		{
			if (!ft_strncmp(cmd_split[0], env_split[0], ft_strlen(cmd_split[0])))
				return (i);
		}
		else if (ft_strlen(cmd_split[0]) < ft_strlen(env_split[0]))
		{
			if (!ft_strncmp(cmd_split[0], env_split[0], ft_strlen(env_split[0])))
				return (i);
		}
	}
	return (0);
}

int	contains_str(char **envp, char *str)
{
	int	i;
	char **cmd_split;
	char **env_split;

	i = 0;
	cmd_split = ft_split(str, '=');
	while(envp[i])
	{
		env_split = ft_split(envp[i],'=');
		if (ft_strlen(cmd_split[0]) > ft_strlen(env_split[0]))
		{
			if (!ft_strncmp(cmd_split[0], env_split[0], ft_strlen(cmd_split[0])))
				return (1);
		}
		else if (ft_strlen(cmd_split[0]) < ft_strlen(env_split[0]))
		{
			if (!ft_strncmp(cmd_split[0], env_split[0], ft_strlen(env_split[0])))
				return (1);
		}
		i++;
	}
	return (0);
}

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

void	ft_export(char **cmd, char ***envp)
{
	int		i;
	int		j;
	char	**new_envp;
	int		argc;

	i = 0;
	argc = get_array_size(cmd);
	if (argc == 1)
	{
		sort_envp(*envp);
		while ((*envp)[i])
		{
			if (ft_strncmp((*envp)[i], "_=", 2) != 0)
				printf("%s\n", (*envp)[i]);
			i++;
		}
	}
	else if (argc > 1)
	{
		new_envp = malloc(sizeof(char *) * (get_array_size(*envp) + argc));
		if (!new_envp)
			return ;
		while ((*envp)[i])
		{
			new_envp[i] = (*envp)[i];
			i++;
		}
		j = 1;
		while (j < argc)
		{
			if (!contains_str(*envp, cmd[j]))
				new_envp[i] = ft_strdup(cmd[j]);
			else
				new_envp[get_str_index(*envp, cmd[j])] = ft_strdup(cmd[j]);
			j++;
			i++;
		}
		new_envp[i] = NULL;
		*envp = new_envp;
	}
}
