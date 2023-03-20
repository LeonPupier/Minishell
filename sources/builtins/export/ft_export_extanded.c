/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_extanded.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:55:29 by vcart             #+#    #+#             */
/*   Updated: 2023/03/20 15:17:31 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	export_other_case(char **cmd, t_list *new_envp, int i)
{
	char	**cmd_split;
	char	*str_no_plus;

	cmd_split = ft_split(cmd[i], '=');
	str_no_plus = remove_plus(cmd_split[0]);
	if (cmd_split[0][ft_strlen(cmd_split[0]) - 1] == '+' && \
	ft_list_contains(new_envp, str_no_plus, 0))
	{
		treat_plus_sign(cmd, cmd_split, \
		new_envp, i);
	}
	else if (!ft_list_contains(new_envp, cmd_split[0], 0))
		treat_special_case(cmd, new_envp, cmd_split, i);
	else
		export_new_value(cmd, cmd_split, new_envp, i);
	free(str_no_plus);
}

void	treat_plus_sign(char **cmd, char **cmd_split, \
t_list *new_envp, int i)
{
	int		j;
	char	*str_no_plus;

	str_no_plus = remove_plus(cmd_split[0]);
	if (count_equals(cmd[i]) > 1)
	{
		j = 0;
		while (j < count_equals(cmd[i]))
		{
			(ft_list_find(new_envp, str_no_plus, 0)) \
			->content = ft_strjoin((ft_list_find(new_envp, \
			str_no_plus, 0))->content, ft_strdup("="));
			j++;
		}
	}
	(ft_list_find(new_envp, str_no_plus, 0)) \
	->content = ft_strjoin((ft_list_find(new_envp, \
	str_no_plus, 0))->content, cmd_split[1]);
	free(cmd_split[0]);
	free(cmd_split);
}

void	export_new_value(char **cmd, char **cmd_split, t_list *new_envp\
, int i)
{
	t_list	*tmp;

	if (cmd_split[1][0] == '$')
	{
		if (ft_strcmp(cmd_split[1] + 1, cmd_split[0]))
			treat_dollar_sign(new_envp, cmd_split);
	}
	else
	{
		tmp = (ft_list_find(new_envp, cmd_split[0], 0));
		free(tmp->content);
		tmp->content = ft_strdup(cmd[i]);
		free_tab(cmd_split);
	}
}

void	change_known_var(char **cmd, t_list *new_envp, int i)
{
	char	**cmd_split;

	cmd_split = ft_split(cmd[i], '=');
	free(ft_list_find(new_envp, cmd_split[0], 0)->content);
	ft_list_find(new_envp, cmd_split[0], 0)->content = ft_strdup(cmd[i]);
	free_tab(cmd_split);
}

void	replace_dollar_value(t_list *envp, char **cmd_split)
{
	char	**elt;
	char	*elt_to_split;
	t_list	*tmp;
	char	*cmd[3];

	if (ft_list_contains(envp, cmd_split[0], 0))
	{
		cmd[0] = "unset";
		cmd[1] = cmd_split[0];
		cmd[2] = NULL;
		ft_unset(cmd, envp);
	}
	tmp = ft_list_find(envp, cmd_split[1] + 1, 0);
	elt_to_split = tmp->content;
	elt = ft_split(elt_to_split, '=');
	free(tmp);
	free(elt_to_split);
	free(cmd_split[1]);
	cmd_split[0] = ft_strjoin(cmd_split[0], ft_strdup("="));
	cmd_split[1] = elt[1];
	ft_list_push_back(&envp, ft_strjoin(cmd_split[0], cmd_split[1]));
	free_tab(elt);
}
