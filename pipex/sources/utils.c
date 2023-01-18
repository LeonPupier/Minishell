/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:30:22 by vcart             #+#    #+#             */
/*   Updated: 2023/01/18 12:48:23 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**get_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			return (ft_split(ft_strdup(envp[i] + 5), ':'));
		i++;
	}
	return (NULL);
}

char	*get_binary_path(char *cmd, char **envp)
{
	char	**path_list;
	char	*path;
	char	*result;
	int		i;

	path_list = get_env_path(envp);
	i = 0;
	while (path_list[i])
	{
		path = ft_strjoin(path_list[i], "/");
		result = ft_strjoin(path, cmd);
		free(path);
		if (access(result, F_OK | X_OK) == 0)
		{
			while (path_list[i])
			{
				free(path_list[i]);
				i++;
			}
			return (free(path_list), result);
		}
		free(path_list[i]);
		i++;
	}
	return (0);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
