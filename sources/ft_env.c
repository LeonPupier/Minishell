/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:45:59 by vcart             #+#    #+#             */
/*   Updated: 2023/02/08 19:56:29 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env(char **cmd, char **envp)
{
	int	i;

	i = 0;
	if (cmd[1] == NULL)
	{
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
	}
	else
		printf("\e[31menv: too many arguments\e[0m\n");
}

void	sort_envp(t_list *start)
{
	int		swapped;
	t_list	*ptrl;
	t_list	*lptr;

	if (start == NULL)
		return ;
	swapped = 1;
	lptr = NULL;
	while (swapped)
	{
		swapped = 0;
		ptrl = start;
		while (ptrl->next != lptr)
		{
			if (ft_strcmp(ptrl->content, ptrl->next->content) > 0)
			{
				swap_nodes(ptrl, ptrl->next);
				swapped = 1;
			}
			ptrl = ptrl->next;
		}
		lptr = ptrl;
	}
}

t_list	*envp_to_list(char **envp)
{
	t_list	*begin_list;
	t_list	*first;
	int		i;

	begin_list = ft_create_elem(envp[0]);
	first = begin_list;
	i = 1;
	while (envp[i])
	{
		begin_list->next = ft_create_elem(envp[i]);
		begin_list = begin_list->next;
		i++;
	}
	return (first);
}
