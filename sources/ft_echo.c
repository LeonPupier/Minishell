/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:25:09 by lpupier           #+#    #+#             */
/*   Updated: 2023/01/20 14:40:43 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	if (!cmd[1])
	{
		printf("\n");
		return ;
	}
	tab_size = 0;
	while (cmd[1 + tab_size] != NULL)
		tab_size++;
	if (tab_size >= 1)
	{
		count = 1;
		while (!ft_strncmp(cmd[count], "-n", 2))
			count++;
		while (cmd[count] != NULL)
		{
			if (cmd[count][0] != '\0')
			{
				printf("%s", cmd[count]);
				if (count < tab_size)
					printf(" ");
			}
			count++;
		}
	}
	if (ft_strncmp(cmd[1], "-n", 2))
		printf("\n");
}
