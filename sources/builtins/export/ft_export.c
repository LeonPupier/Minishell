/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:14:04 by vcart             #+#    #+#             */
/*   Updated: 2023/03/11 19:16:54 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
	result[size] = NULL;
	if (!result)
		return (NULL);
	while (list)
	{
		result[i] = ft_strdup(list->content);
		if (!result[i])
			return (free_tab(result), NULL);
		list = list->next;
		i++;
	}
	return (result);
}

int	strlen_noplus(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != '+')
			count++;
		i++;
	}
	return (count);
}

char	*remove_plus(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(sizeof(char) * (strlen_noplus(str) + 1));
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '+')
		{
			result[j] = str[i];
			j++;
		}
		i++;
	}
	result[j] = 0;
	return (result);
}

void	ft_export(char **cmd, t_list *new_envp)
{
	int		argc;

	argc = get_array_size(cmd);
	if (argc == 1)
		print_export(new_envp);
	else if (argc > 1)
	{
		if (check_export_error(cmd, argc) == -1)
			return ;
		if (treat_empty_value(cmd, cmd[1], new_envp))
			return ;
		else
		{
			treat_export(cmd, new_envp, argc);
		}
	}
}
