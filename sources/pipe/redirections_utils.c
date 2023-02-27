/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart < vcart@student.42lyon.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:24:56 by vcart             #+#    #+#             */
/*   Updated: 2023/02/27 15:44:18 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	get_infiles_index(char **cmd)
{
	int	i;

	i = 0;
	if (!check_infiles(cmd))
		return (-1);
	while (cmd[i] != NULL)
	{
		if (!ft_strcmp(cmd[i], ">") || !ft_strcmp(cmd[i], ">>"))
			return (i);
		i++;
	}
	return (0);
}

void	handle_infiles(char **cmd, t_env *env, int status)
{
	int	i;
	int	fd;
	char **command;

	i = get_infiles_index(cmd);
	if (i == -1)
		return ;
	if (check_infiles(cmd) == 1)
	{
		fd = open(cmd[i + 1], O_RDONLY);
		if (fd == -1)
		{
			perror("Open error\n");
			return ;
		}
	}
	command = malloc(sizeof(char *));
	command[0] = cmd[i + 2];
	dup2(fd, STDIN_FILENO);
	if (status == 0)
		dup2(fd, STDOUT_FILENO);
	close(fd);
	check_functions(command, env, 1);
	if (status == 1)
		dup2(1, STDIN_FILENO);
	free(command);
}
