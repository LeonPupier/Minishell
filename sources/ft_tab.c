/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:25:33 by vcart             #+#    #+#             */
/*   Updated: 2023/02/08 20:26:55 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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