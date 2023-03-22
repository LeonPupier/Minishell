/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_extended.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:14:26 by vcart             #+#    #+#             */
/*   Updated: 2023/03/22 16:19:26 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_next_fd(int *next_fd, char **cmd)
{
	if (check_redirections(cmd))
	{
		if (make_redirections(cmd) == -1)
			return (-1);
	}
	else
	{
		close(next_fd[0]);
		if (dup2(next_fd[1], STDOUT_FILENO) == -1)
			return (-1);
		close(next_fd[1]);
	}
	return (0);
}
