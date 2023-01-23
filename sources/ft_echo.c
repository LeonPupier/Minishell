/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:25:09 by lpupier           #+#    #+#             */
/*   Updated: 2023/01/23 15:08:02 by lpupier          ###   ########.fr       */
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
	int	count;

	if (!cmd[1])
	{
		printf("\n");
		return ;
	}
	count = 1;
	while (cmd[count] && !ft_strncmp(cmd[count], "-n", 2))
	{
		while (cmd[count] && !ft_strncmp(cmd[count], "-n", 2))
			count++;
	}
	while (cmd[count] != NULL)
	{
		if (cmd[count][0] != '\0')
		{
			printf("%s", cmd[count]);
			if (count < get_array_size(cmd) - 1)
				printf(" ");
		}
		count++;
	}
	if (ft_strncmp(cmd[1], "-n", 2))
		printf("\n");
}
