/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:55:19 by vcart             #+#    #+#             */
/*   Updated: 2023/03/10 17:27:38 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	count_plus(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '+')
			count++;
		i++;
	}
	return (count);
}

int	get_equal_index(char *export_cmd)
{
	int	i;

	i = 0;
	while (export_cmd[i])
	{
		if (export_cmd[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	treat_empty_value(char **cmd, char *export_cmd, t_list *new_envp)
{
	int		i;
	char	**split_cmd;
	char	*to_add;
	t_list	*tmp;

	i = get_equal_index(export_cmd);
	if (i == -1)
		return (1);
	if (export_cmd[i + 1] == '\0')
	{
		split_cmd = ft_split(export_cmd, '=');
		to_add = ft_strjoin(cmd[1], ft_strdup(""));
		if (!ft_list_contains(new_envp, split_cmd[0], 0))
			ft_lstadd_back(&new_envp, ft_lstnew(to_add));
		else
		{
			tmp = ft_list_find(new_envp, split_cmd[0], 0);
			free(tmp->content);
			tmp->content = to_add;
		}
		free_tab(split_cmd);
		return (1);
	}
	else if (i == 0)
	{
		printf("%s \e[31m: not a valid identifier\e[0m\n", export_cmd);
		return (1);
	}
	return (0);
}

void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->content);
		free(tmp);
	}
}
