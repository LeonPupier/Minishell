/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:45:59 by vcart             #+#    #+#             */
/*   Updated: 2023/03/18 14:55:51 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	env(char **cmd, t_list *new_envp)
{
	if (cmd[1] == NULL)
	{
		while (new_envp)
		{
			printf("%s\n", (char *)new_envp->content);
			new_envp = new_envp->next;
		}
		return (0);
	}
	else
		printf("\e[31menv: too many arguments\e[0m\n");
	return (127);
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

	begin_list = ft_create_elem(ft_strdup(envp[0]));
	first = begin_list;
	i = 1;
	while (envp[i] && begin_list)
	{
		begin_list->next = ft_create_elem(ft_strdup(envp[i]));
		begin_list = begin_list->next;
		i++;
	}
	return (first);
}
