/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:18:47 by vcart             #+#    #+#             */
/*   Updated: 2023/03/10 18:15:15 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
			if (count_plus(cmd_split[0]) > 1)
			{
				printf("%s \e[31m: not a valid identifier\e[0m\n", cmd[i]);
				free_tab(cmd_split);
				return (-1);
			}
			else if (contains("0123456789", cmd_split[0][0]) || \
				contains(cmd_split[0], '-'))
			{
				printf("%s \e[31m: not a valid identifier\e[0m\n", cmd[i]);
				free_tab(cmd_split);
				return (-1);
			}
			free_tab(cmd_split);
		}
		i++;
	}
	return (0);
}

void	print_export(t_list *new_envp)
{
	char	**envp_split;

	sort_envp(new_envp);
	while (new_envp)
	{
		if (ft_strncmp(new_envp->content, "_=", 2) != 0)
		{
			envp_split = ft_split(new_envp->content, '=');
			if (envp_split[1])
				printf("declare -x %s=\"%s\"\n", envp_split[0], envp_split[1]);
			else if (!envp_split[1])
				printf("declare -x %s=\"\"\n", envp_split[0]);
			free_tab(envp_split);
		}
		new_envp = new_envp->next;
	}
}

void	treat_dollar_sign(t_list *envp, char **cmd_split)
{
	char	**elt;
	char	*cmd[3];

	if (cmd_split[1][0] == '$' && \
	ft_list_contains(envp, cmd_split[1] + 1, 0))
	{
		if (ft_list_contains(envp, cmd_split[0], 0))
		{
			cmd[0] = "unset";
			cmd[1] = cmd_split[0];
			cmd[2] = NULL;
			ft_unset(cmd, envp);
		}
		elt = ft_split(ft_strdup((ft_list_find(\
		envp, cmd_split[1] + 1, 0)->content)), '=');
		free(cmd_split[1]);
		cmd_split[0] = ft_strjoin(cmd_split[0], ft_strdup("="));
		cmd_split[1] = elt[1];
		ft_list_push_back(&envp, ft_strjoin(cmd_split[0], cmd_split[1]));
		free_tab(elt);
	}
	else if (cmd_split[1][0] == '$' && \
	!ft_list_contains(envp, cmd_split[1] + 1, 0))
	{
		cmd_split[0] = ft_strjoin(cmd_split[0], ft_strdup("="));
		cmd_split[1] = ft_strdup("");
		ft_list_push_back(&envp, ft_strjoin(cmd_split[0], cmd_split[1]));
	}
}

void	treat_special_case(char **cmd, t_list *envp, char **cmd_split, int i)
{
	if (cmd_split[1][0] == '$')
	{
		if (ft_strcmp(cmd_split[1] + 1, cmd_split[0]))
			treat_dollar_sign(envp, cmd_split);
	}
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
			{
				(ft_list_find(new_envp, remove_plus(cmd_split[0]), 0)) \
				->content = ft_strjoin((ft_list_find(new_envp, \
				remove_plus(cmd_split[0]), 0))->content, cmd_split[1]);
				free(cmd_split[0]);
			}
			else if (!ft_list_contains(new_envp, cmd_split[0], 0))
				treat_special_case(cmd, new_envp, cmd_split, i);
			else
			{
				if (cmd_split[1][0] == '$')
				{
					if (ft_strcmp(cmd_split[1] + 1, cmd_split[0]))
						treat_dollar_sign(new_envp, cmd_split);
				}
				else
				{
					(ft_list_find(new_envp, cmd_split[0] \
					, 0))->content = ft_strdup(cmd[i]);
					free_tab(cmd_split);
				}
			}
		}
		i++;
	}
}
