/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:19:49 by lpupier           #+#    #+#             */
/*   Updated: 2023/02/27 22:08:59 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_quotes(char ***cmd, char *str, t_parsing *parsing)
{
	if (str[parsing->idx] == '"' || str[parsing->idx] == '\'')
	{
		parsing->c = str[parsing->idx];
		parsing->idx++;
		while (str[parsing->idx] && str[parsing->idx] != parsing->c)
			parsing->idx++;
		if (!str[parsing->idx])
			return (0);
		while (str[parsing->idx] && str[parsing->idx] != ' ')
			parsing->idx++;
		*cmd = add_to_tab(*cmd, removing_quotes(get_var(\
		ft_substr(str, parsing->idx_init, parsing->idx - parsing->idx_init), \
				parsing->envp)));
		parsing->idx_init = parsing->idx;
	}
	return (1);
}

char	*removing_quotes(char *str)
{
	char	*new_str;
	int		idx;
	int		new_idx;
	int		len;
	char	caracter;

	caracter = 0;
	len = 0;
	idx = -1;
	while (str[++idx])
	{
		if (str[idx] == caracter)
			caracter = 0;
		else if ((str[idx] == '"' || str[idx] == '\'') && caracter == 0)
			caracter = str[idx];
		else
			len++;
	}
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	idx = -1;
	new_idx = 0;
	while (str[++idx])
	{
		if (str[idx] == caracter)
			caracter = 0;
		else if ((str[idx] == '"' || str[idx] == '\'') && caracter == 0)
			caracter = str[idx];
		else
		{
			new_str[new_idx] = str[idx];
			new_idx++;
		}
	}
	return (free(str), new_str[new_idx] = '\0', new_str);
}
