/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:25:09 by lpupier           #+#    #+#             */
/*   Updated: 2023/01/19 18:12:34 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
static void	putstr_for_echo(char *str)
{
	int		idx;
	int		new_idx;
	char	*var;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == '$')
		{
			idx++;
			new_idx = idx;
			while (str[new_idx] && ft_isalpha(str[new_idx]))
				new_idx++;
			var = ft_substr(str, idx, new_idx - 1);
			if (getenv(var))
				printf("%s", getenv(var));
			free(var);
			idx = new_idx;
			continue ;
		}
		else
			printf("%c", str[idx]);
		idx++;
	}
}
*/

/**
 * @brief Echo the STRING(s) to standard output.
 * 
 * @param cmd List of character strings representing.
 * the command typed by the user.
 */
void	echo(char **cmd)
{
	int	tab_size;
	int	count;

	tab_size = 0;
	while (cmd[1 + tab_size] != NULL)
		tab_size++;
	if (tab_size >= 1)
	{
		if (!ft_strncmp(cmd[1], "-n", 2))
			count = 2;
		else
			count = 1;
		while (cmd[count] != NULL)
		{
			//putstr_for_echo(cmd[count]);
			printf("%s", cmd[count]);
			if (count < tab_size)
				printf(" ");
			count++;
		}
	}
	if (ft_strncmp(cmd[1], "-n", 2))
		printf("\n");
}
