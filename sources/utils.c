/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:26:01 by lpupier           #+#    #+#             */
/*   Updated: 2023/02/07 14:09:43 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env(char **envp, char *request)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], request, ft_strlen(request)) == 0)
			return (ft_strdup(envp[i] + ft_strlen(request) + 1));
		i++;
	}
	return (NULL);
}

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

int	get_array_size(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
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

char	**add_to_tab(char **tab, char **elts, char *elt)
{
	char	**new_tab;
	int		idx;
	int		len_tab;
	int		len_elts;

	len_tab = 0;
	len_elts = 0;
	if (!elts)
		len_elts = 1;
	while (tab[len_tab] != NULL)
		len_tab++;
	while (elts != NULL && elts[len_elts])
		len_elts++;
	new_tab = malloc(sizeof(char *) * (len_tab + len_elts + 1));
	if (!new_tab)
		return (NULL);
	idx = -1;
	while (tab[++idx])
		new_tab[idx] = tab[idx];
	if (!elts)
		new_tab[idx] = elt;
	idx = -1;
	while (elts != NULL && elts[++idx])
		new_tab[len_tab + idx] = elts[idx];
	return (new_tab[len_tab + len_elts] = NULL, new_tab);
}
