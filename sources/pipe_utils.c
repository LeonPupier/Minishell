/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:10:19 by vcart             #+#    #+#             */
/*   Updated: 2023/02/13 12:19:44 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_pipe(char **tab)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tab[i])
	{
		if (!strcmp(tab[i], "|"))
			count++;
		i++;
	}
	return (count);
}

int	*get_pipe_index(char **tab)
{
	int	*pipe_tab;
	int	i;
	int	j;

	if (count_pipe(tab))
	{
		pipe_tab = malloc(sizeof(int) * (count_pipe(tab) + 1));
		if (!pipe_tab)
			return (NULL);
		i = 0;
		j = 0;
		while (tab[i])
		{
			if (!strcmp(tab[i], "|"))
			{
				pipe_tab[j] = i;
				j++;
			}
			i++;
		}
		return (pipe_tab);
	}
	return (NULL);
}
