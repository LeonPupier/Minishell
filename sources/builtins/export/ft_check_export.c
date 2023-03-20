/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:18:47 by vcart             #+#    #+#             */
/*   Updated: 2023/03/20 18:13:15 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_export_error(char *cmd)
{
	char	**cmd_split;

	if (ft_strlen(cmd) == 1 && !ft_isalpha(cmd[0]))
		return (printf("%s \e[31m: not a valid identifier\e[0m\n", \
		cmd), -1);
	else if (count_equals(cmd) == (int)ft_strlen(cmd))
		return (printf("%s \e[31m: not a valid identifier\e[0m\n", \
		cmd), -1);
	else
	{
		cmd_split = ft_split(cmd, '=');
		if (check_prompt_error(cmd, cmd_split) == -1)
			return (free_tab(cmd_split), -1);
		else if (ft_strlen(cmd_split[0]) == 1 && \
		!ft_isalpha(cmd_split[0][0]))
			return (printf("%s \e[31m: not a valid identifier\e[0m\n", \
			cmd), free_tab(cmd_split), -1);
		free_tab(cmd_split);
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
			if (get_equal_index(new_envp->content) == -1)
				printf("declare -x %s\n", (char *)new_envp->content);
			else if (count_equals(new_envp->content) > 1)
				print_export_equals(new_envp);
			else
			{
				envp_split = ft_split(new_envp->content, '=');
				if (envp_split[1])
					printf("declare -x %s=\"%s\"\n", envp_split[0], envp_split[1]);
				else if (!envp_split[1])
					printf("declare -x %s=\"\"\n", envp_split[0]);
				free_tab(envp_split);
			}
		}
		new_envp = new_envp->next;
	}
}

void	treat_dollar_sign(t_list *envp, char **cmd_split)
{
	if (cmd_split[1][0] == '$' && \
	ft_list_contains(envp, cmd_split[1] + 1, 0))
	{
		replace_dollar_value(envp, cmd_split);
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
	if (count_equals(cmd[i]) > 1)
		treat_multiple_equals(cmd[i], envp);
	else if (cmd_split[1][0] == '$')
	{
		if (ft_strcmp(cmd_split[1] + 1, cmd_split[0]))
			treat_dollar_sign(envp, cmd_split);
	}
	else if (cmd_split[0][ft_strlen(cmd_split[0]) - 1] == '+')
		ft_list_push_back(&envp, remove_plus(cmd[i]));
	else
		ft_list_push_back(&envp, ft_strdup(cmd[i]));
	free_tab(cmd_split);
}

void	treat_export(char **cmd, t_list *new_envp, int argc)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (check_export_error(cmd[i]) == -1 || \
		treat_empty_value(cmd, cmd[i], new_envp, i))
		{
			i++;
			continue ;
		}
		else if (ft_list_contains(new_envp, cmd[i], 3) && contains(cmd[i], '='))
			change_known_var(cmd, new_envp, i);
		else if (!ft_list_contains(new_envp, cmd[i], 3) && \
		!contains(cmd[i], '='))
			ft_list_push_back(&new_envp, ft_strdup(cmd[i]));
		else
			export_other_case(cmd, new_envp, i);
		i++;
	}
}
