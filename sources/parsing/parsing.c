/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 12:28:56 by lpupier           #+#    #+#             */
/*   Updated: 2023/02/27 18:26:07 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**cmd_parsing(char **cmd, char *str, char **envp)
{
	t_parsing	parsing;

	parsing.idx = 0;
	parsing.idx_init = 0;
	parsing.envp = envp;
	while (str[parsing.idx])
	{
		if (str[parsing.idx] == ' ')
		{
			if (str[parsing.idx - 1] != ' ' && parsing.idx_init != parsing.idx)
				cmd = add_to_tab(cmd, get_var(ft_substr(str, parsing.idx_init, \
						parsing.idx - parsing.idx_init), envp));
			parsing.idx_init = parsing.idx + 1;
		}
		else if (!parse_quotes(&cmd, str, &parsing))
			continue ;
		parsing.idx++;
	}
	if (str[parsing.idx - 1] == ' ')
		return (cmd);
	return (cmd = add_to_tab(cmd, get_var(ft_substr(str, parsing.idx_init, \
				parsing.idx - parsing.idx_init), envp)), cmd);
}
