/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:10:19 by vcart             #+#    #+#             */
/*   Updated: 2023/03/09 20:50:23 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_pipe(char ***cmd_tab)
{
	int	nb_pipe;

	nb_pipe = 0;
	while (cmd_tab[nb_pipe] != NULL)
		nb_pipe++;
	return (nb_pipe);
}

int	check_redirections(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (!ft_strcmp(cmd[i], ">"))
			return (1);
		else if (!ft_strcmp(cmd[i], ">>"))
			return (2);
		i++;
	}
	return (0);
}

int	check_infiles(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (!ft_strcmp(cmd[i], "<"))
			return (1);
		else if (!ft_strcmp(cmd[i], "<<"))
			return (2);
		i++;
	}
	return (0);
}

int	get_redirections_index(char **cmd)
{
	int	i;

	i = 0;
	if (!check_redirections(cmd))
		return (-1);
	while (cmd[i] != NULL)
	{
		if (!ft_strcmp(cmd[i], ">") || !ft_strcmp(cmd[i], ">>"))
			return (i);
		i++;
	}
	return (0);
}

void	make_redirections(char **cmd)
{
	int	i;
	int	fd;
	int	state;

	i = get_redirections_index(cmd);
	if (i == -1)
		return ;
	if (check_redirections(cmd) == 1)
		state = O_TRUNC;
	else if (check_redirections(cmd) == 2)
		state = O_APPEND;
	fd = open(cmd[i + 1], O_WRONLY | O_CREAT | state, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	cmd[i] = NULL;
}
