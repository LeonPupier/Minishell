/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:10:19 by vcart             #+#    #+#             */
/*   Updated: 2023/03/29 12:13:06 by vcart            ###   ########.fr       */
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
	int	last_index;

	i = 0;
	last_index = 0;
	while (cmd[i] != NULL)
	{
		if (!ft_strcmp(cmd[i], ">"))
			last_index = 1;
		else if (!ft_strcmp(cmd[i], ">>"))
			last_index = 2;
		i++;
	}
	return (last_index);
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

int	make_redirections(char **cmd)
{
	int	i;
	int	fd;
	int	state;
	int	last_index;

	i = 0;
	last_index = get_redirections_index(cmd);
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], ">") || !ft_strcmp(cmd[i], ">>"))
		{
			if (cmd[i + 1] == NULL || contains("<>", cmd[i + 1][0]))
				return (perror("minishell : syntax error near \
				unexpected token 'newline'"), -1);
			if (check_redirections(cmd) == 1)
				state = O_TRUNC;
			else if (check_redirections(cmd) == 2)
				state = O_APPEND;
			fd = open(cmd[i + 1], O_WRONLY | O_CREAT | state, 0644);
			if (fd == -1)
				return (perror("minishell : open"), -1);
			if (dup2(fd, STDOUT_FILENO) == -1)
				return (-1);
			close(fd);
		}
		i++;
	}
	free_redirections(last_index, cmd);
	return (0);
}
