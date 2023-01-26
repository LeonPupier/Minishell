/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:07:53 by lpupier           #+#    #+#             */
/*   Updated: 2023/01/26 11:17:15 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstdelone(t_list **head_lst, char *data_ref)
{
	t_list	*temp;
	t_list	*prev;
	char	**to_compare;

	temp = *head_lst;
	to_compare = ft_split(temp->content, '=');
	if (temp && !ft_strcmp(to_compare[0], data_ref))
	{
		*head_lst = temp->next;
		free(temp);
		free_tab(to_compare);
		return;
	}
	while (temp && ft_strcmp(to_compare[0], data_ref) != 0)
	{
		prev = temp;
		temp = temp->next;
        free_tab(to_compare);
		to_compare = ft_split(temp->content, '=');
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	free(temp);
	
}

void	ft_unset(char **cmd, t_list *new_envp)
{
	int		i;
	int		argc;

	argc = get_array_size(cmd);
	if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			if (contains (cmd[i], '='))
			{
				printf("%s \e[31m: not a valid identifier\e[0m\n", cmd[i]);
				return ;
			}
			else if (ft_list_contains(new_envp, cmd[i], 0))
				ft_lstdelone(&new_envp, cmd[i]);
			i++;
		}
	}
}