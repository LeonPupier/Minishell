/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:25:33 by vcart             #+#    #+#             */
/*   Updated: 2023/03/22 16:07:00 by vcart            ###   ########.fr       */
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
	len_tab = get_array_size(tab);
	new_tab = malloc(sizeof(char *) * (len_tab + 2));
	if (!new_tab)
		return (free(elt), free_tab(tab), NULL);
	idx = -1;
	while (tab[++idx])
	{
		new_tab[idx] = ft_strdup(tab[idx]);
		if (!new_tab[idx])
			return (free_tab(tab), NULL);
	}
	new_tab[idx] = ft_strdup(elt);
	if (!new_tab[idx])
		return (free_tab(tab), NULL);
	new_tab[idx + 1] = NULL;
	return (free(elt), free_tab(tab), new_tab);
}
