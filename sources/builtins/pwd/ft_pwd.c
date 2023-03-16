/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:35:40 by vcart             #+#    #+#             */
/*   Updated: 2023/03/14 10:51:28 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief Print name of current/working directory.
 * 
 * @param cmd List of character strings representing.
 * @param envp Environment instructions.
 */
int	pwd(char **cmd, char **envp)
{
	char	*pwd;

	if (cmd[1] == NULL)
	{
		pwd = get_env(envp, "PWD");
		printf("%s\n", pwd);
		free(pwd);
		return (0);
	}
	else
		printf("\e[31mpwd: too many arguments\e[0m\n");
	return (1);
}
