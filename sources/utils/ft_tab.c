/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:25:33 by vcart             #+#    #+#             */
/*   Updated: 2023/03/13 14:14:55 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char **tab)
{
	int	idx;

	idx = 0;
	while (tab[idx])
	{
		if (tab[idx])
			free(tab[idx]);
		idx++;
	}
	free(tab);
}

void	free_2tab(char ***tab)
{
	int	idx;

	idx = 0;
	while (tab[idx])
	{
		free_tab(tab[idx]);
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

char	**add_to_tab(char **tab, char *elt)
{
	char	**new_tab;
	int		idx;
	int		len_tab;

	if (!elt)
		return (tab);
	else if (!elt[0])
		return (free(elt), tab);
	len_tab = 0;
	while (tab[len_tab] != NULL)
		len_tab++;
	new_tab = malloc(sizeof(char *) * (len_tab + 2));
	if (!new_tab)
		return (free(elt), free_tab(tab), NULL);
	idx = -1;
	while (tab[++idx])
	{
		new_tab[idx] = ft_strdup(tab[idx]);
		if (!new_tab[idx])
			free_tab(tab);
	}
	new_tab[idx] = ft_strdup(elt);
	new_tab[idx + 1] = NULL;
	return (free(elt), free_tab(tab), new_tab);
}
