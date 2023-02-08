/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:26:01 by lpupier           #+#    #+#             */
/*   Updated: 2023/02/08 19:38:32 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_in_envp(char **envp, char *request)
{
	int		i;
	char	**env_split;

	i = 0;
	while (envp[i])
	{
		env_split = ft_split(envp[i], '=');
		if (!ft_strcmp(env_split[0], request))
			return (1);
		free_tab(env_split);
		i++;
	}
	return (0);
}

char	*get_env(char **envp, char *request)
{
	int	i;

	i = 0;
	if (!is_in_envp(envp, request))
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], request, ft_strlen(request)) == 0)
			return (ft_strdup(envp[i] + ft_strlen(request) + 1));
		i++;
	}
	return (NULL);
}

char	*get_binary_path(char *cmd, char **envp)
{
	char	**path_list;
	char	*path;
	char	*result;
	char	*env;
	int		i;

	env = get_env(envp, "PATH");
	path_list = ft_split(env, ':');
	free(env);
	i = -1;
	while (path_list[++i])
	{
		path = ft_strjoin(ft_strdup(path_list[i]), ft_strdup("/"));
		result = ft_strjoin(path, ft_strdup(cmd));
		if (access(result, F_OK | X_OK) == 0)
			return (free_tab(path_list), result);
		free(result);
	}
	free_tab(path_list);
	return (ft_strdup(cmd));
}

char	**add_to_tab(char **tab, char *elt)
{
	char	**new_tab;
	int		idx;
	int		len_tab;

	len_tab = 0;
	while (tab[len_tab] != NULL)
		len_tab++;
	new_tab = malloc(sizeof(char *) * (len_tab + 2));
	if (!new_tab)
		return (free(elt), free(tab), NULL);
	idx = 0;
	while (tab[idx])
	{
		new_tab[idx] = ft_strdup(tab[idx]);
		idx++;
	}
	new_tab[idx] = ft_strdup(elt);
	new_tab[idx + 1] = NULL;
	return (free(elt), free(tab), new_tab);
}