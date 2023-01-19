/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:45:59 by vcart             #+#    #+#             */
/*   Updated: 2023/01/19 17:18:30 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env(char **cmd, char **envp)
{
	int	i;

	i = 0;
	if (cmd[1] == NULL)
	{
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
	}
	else
		printf("\e[31menv: too many arguments\e[0m\n");
}
