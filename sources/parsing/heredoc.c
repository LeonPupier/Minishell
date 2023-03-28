/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:43:56 by lpupier           #+#    #+#             */
/*   Updated: 2023/03/28 17:18:06 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_heredoc(char ***cmd, char *str, t_parsing *parsing)
{
	char	*heredoc;

	heredoc = NULL;
	if (!ft_strncmp(str + parsing->idx, ">>", 2))
		heredoc = ">>";
	else if (!ft_strncmp(str + parsing->idx, "<<", 2))
		heredoc = "<<";
	else if (!ft_strncmp(str + parsing->idx, ">", 1))
		heredoc = ">";
	else if (!ft_strncmp(str + parsing->idx, "<", 1))
		heredoc = "<";
	if (heredoc)
	{
		*cmd = add_to_tab(*cmd, get_var(ft_substr(str, parsing->idx_init, \
							parsing->idx - parsing->idx_init), parsing->envp));
		*cmd = add_to_tab(*cmd, ft_strdup(heredoc));
		parsing->idx_init = parsing->idx + ft_strlen(heredoc);
		if (ft_strlen(heredoc) == 2)
			parsing->idx++;
		return (1);
	}
	return (0);
}
