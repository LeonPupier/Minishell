/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:28:56 by lpupier           #+#    #+#             */
/*   Updated: 2023/03/28 17:18:29 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**cmd_parsing(char **cmd, char *str, char **envp)
{
	t_parsing	parsing;
	char		*var;

	parsing.idx = 0;
	parsing.idx_init = 0;
	parsing.envp = envp;
	loop_parsing(&cmd, str, envp, &parsing);
	if (is_ws(str[ft_strlen(str) - 1]))
		return (cmd);
	var = ft_substr(str, parsing.idx_init, parsing.idx - parsing.idx_init);
	cmd = add_to_tab(cmd, get_var(var, envp));
	return (cmd);
}

void	loop_parsing(char ***cmd, char *str, char **envp, \
							t_parsing *parsing)
{
	char	*var;

	var = NULL;
	while (str[parsing->idx])
	{
		if (is_ws(str[parsing->idx]))
		{
			if ((parsing->idx == 0 || is_ws(str[parsing->idx - 1]) == 0) \
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
		parse_heredoc(cmd, str, parsing);
		parsing->idx++;
		if ((size_t)parsing->idx >= ft_strlen(str))
			break ;
	}
}

int	is_ws(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' \
		|| c == '\f' || c == '\r' || c == '\v')
		return (1);
	return (0);
}

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_ws(str[i]))
			return (0);
		i++;
	}
	return (1);
}
