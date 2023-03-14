/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:28:56 by lpupier           #+#    #+#             */
/*   Updated: 2023/03/13 13:55:15 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*loop_parsing(char ***cmd, char *str, char **envp, \
							t_parsing *parsing)
{
	char	*var;

	var = NULL;
	while (str[parsing->idx])
	{
		if (str[parsing->idx] == ' ')
		{
			if ((parsing->idx == 0 || str[parsing->idx - 1] != ' ') \
				&& parsing->idx_init != parsing->idx)
			{
				var = ft_substr(str, parsing->idx_init, \
						parsing->idx - parsing->idx_init);
				*cmd = add_to_tab(*cmd, get_var(var, envp));
			}
			parsing->idx_init = parsing->idx + 1;
		}
		else if (!parse_quotes(cmd, str, parsing))
			continue ;
		parsing->idx++;
		if ((size_t)parsing->idx >= ft_strlen(str))
			break ;
	}
	return (var);
}

char	**cmd_parsing(char **cmd, char *str, char **envp)
{
	t_parsing	parsing;
	char		*var;

	parsing.idx = 0;
	parsing.idx_init = 0;
	parsing.envp = envp;
	var = loop_parsing(&cmd, str, envp, &parsing);
	if (str[ft_strlen(str) - 1] == ' ')
		return (cmd);
	var = ft_substr(str, parsing.idx_init, parsing.idx - parsing.idx_init);
	return (cmd = add_to_tab(cmd, get_var(var, envp)), cmd);
}
