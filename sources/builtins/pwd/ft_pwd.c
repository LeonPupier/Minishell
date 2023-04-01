/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:35:40 by vcart             #+#    #+#             */
/*   Updated: 2023/03/27 13:09:30 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief Print name of current/working directory.
 * 
 * @param cmd List of character strings representing.
 * @param envp Environment instructions.
 */
int	pwd(char **cmd)
{
	char	*pwd;

	if (cmd[1] == NULL)
	{
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
			return (-1);
		printf("%s\n", pwd);
		free(pwd);
		return (0);
	}
	else
		printf("\e[31mpwd: too many arguments\e[0m\n");
	return (1);
}
