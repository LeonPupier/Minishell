/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:47:39 by lpupier           #+#    #+#             */
/*   Updated: 2023/02/06 13:26:09 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_list_size(t_list	*begin_list)
{
	int	count;

	count = 0;
	while (begin_list)
	{
		begin_list = begin_list->next;
		count++;
	}
	return (count);
}

char	**list_to_envp(t_list *list)
{
	char	**result;
	int		i;
	int		size;

	size = ft_list_size(list);
	i = 0;
	result = malloc(sizeof(char *) * (size + 1));
	while (list)
	{
		result[i] = ft_strdup(list->content);
		list = list->next;
		i++;
	}
	result[i] = NULL;
	return (result);
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

char	*remove_end(char *str, int del_nb)
{
	char *result;

	result = malloc(sizeof(char) * (ft_strlen(str) - del_nb + 1));
	ft_strlcpy(result, str, ft_strlen(str) - del_nb + 1);
	free(str);
	return (result);
}

void	ft_export(char **cmd, t_list *new_envp)
{
	int		i;
	char	**cmd_split;
	int		argc;

	i = 0;
	argc = get_array_size(cmd);
	if (argc == 1)
	{
		sort_envp(new_envp);
		while (new_envp)
		{
			if (ft_strncmp(new_envp->content, "_=", 2) != 0)
				printf("declare -x %s\n", (char *)(new_envp->content));
			new_envp = new_envp->next;
		}
	}
	else if (argc > 1)
	{
		i = 1;
		while (i < argc)
		{
			if (ft_strlen(cmd[i]) == 1 && !ft_isalpha(cmd[i][0]))
			{
				printf("%s \e[31m: not a valid identifier\e[0m\n", cmd[i]);
				return ;
			}
			else if (!ft_list_contains(new_envp, cmd[i], 3) && !contains(cmd[i], '='))
				ft_list_push_back(&new_envp, ft_strdup(cmd[i]));
			else
			{
				cmd_split = ft_split(cmd[i], '=');
				if (contains("0123456789", cmd_split[0][0]))
				{
					printf("%s \e[31m: not a valid identifier\e[0m\n", cmd[i]);
					return ;
				}
				else if (cmd_split[0][ft_strlen(cmd_split[0]) - 1] == '+' && ft_list_contains(new_envp, remove_end(cmd_split[0], 1), 0))
					(ft_list_find(new_envp, remove_end(cmd_split[0], 1), 0))->content = "test";
				else if (!ft_list_contains(new_envp, cmd_split[0], 0))
				{
					if (cmd_split[1][0] == '$' && ft_list_contains(new_envp, cmd_split[1] + 1, 1))
						ft_list_push_back(&new_envp, ft_strdup((ft_list_find(new_envp, cmd_split[1] + 1, 1)->content)));
					else
						ft_list_push_back(&new_envp, ft_strdup(cmd[i]));
				}
				else
					(ft_list_find(new_envp, cmd_split[0], 0))->content = ft_strdup(cmd[i]);
			}
			i++;
		}
	}
}
