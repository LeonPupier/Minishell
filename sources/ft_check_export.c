/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:18:47 by vcart             #+#    #+#             */
/*   Updated: 2023/02/07 15:59:02 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_export_error(char **cmd, int argc)
{
	int		i;
	char	**cmd_split;

	i = 1;
	while (i < argc)
	{
		if (ft_strlen(cmd[i]) == 1 && !ft_isalpha(cmd[i][0]))
		{
			printf("%s \e[31m: not a valid identifier\e[0m\n", cmd[i]);
			return (-1);
		}
		else
		{
			cmd_split = ft_split(cmd[i], '=');
			if (contains("0123456789", cmd_split[0][0]) || \
			contains(cmd_split[0], '-'))
			{
				printf("%s \e[31m: not a valid identifier\e[0m\n", cmd[i]);
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

void	print_export(t_list *new_envp)
{
	sort_envp(new_envp);
	while (new_envp)
	{
		if (ft_strncmp(new_envp->content, "_=", 2) != 0)
			printf("declare -x %s\n", (char *)(new_envp->content));
		new_envp = new_envp->next;
	}
}

void	treat_special_case(char **cmd, t_list *envp, char **cmd_split, int i)
{
	if (cmd_split[1][0] == '$' && \
	ft_list_contains(envp, cmd_split[1] + 1, 1))
		ft_list_push_back(&envp, ft_strdup((ft_list_find(\
		envp, cmd_split[1] + 1, 1)->content)));
	else if (cmd_split[0][ft_strlen(cmd_split[0]) - 1] == '+')
		ft_list_push_back(&envp, remove_plus(cmd[i]));
	else
		ft_list_push_back(&envp, ft_strdup(cmd[i]));
}

void	treat_export(char **cmd, t_list *new_envp, int argc)
{
	int		i;
	char	**cmd_split;

	i = 1;
	while (i < argc)
	{
		if (!ft_list_contains(new_envp, cmd[i], 3) && !contains(cmd[i], '='))
			ft_list_push_back(&new_envp, ft_strdup(cmd[i]));
		else
		{
			cmd_split = ft_split(cmd[i], '=');
			if (cmd_split[0][ft_strlen(cmd_split[0]) - 1] == '+' && \
			ft_list_contains(new_envp, remove_plus(cmd_split[0]), 0))
				(ft_list_find(new_envp, remove_plus(cmd_split[0]), 0)) \
				->content = ft_strjoin((ft_list_find(new_envp, \
				remove_plus(cmd_split[0]), 0))->content, cmd_split[1]);
			else if (!ft_list_contains(new_envp, cmd_split[0], 0))
				treat_special_case(cmd, new_envp, cmd_split, i);
			else
				(ft_list_find(new_envp, cmd_split[0] \
				, 0))->content = ft_strdup(cmd[i]);
		}
		i++;
	}
}

