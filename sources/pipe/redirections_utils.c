/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:24:56 by vcart             #+#    #+#             */
/*   Updated: 2023/03/09 15:49:28 by vcart            ###   ########.fr       */
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
	int	last_index;

	i = 0;
	last_index = -1;
	if (!check_infiles(cmd))
		return (-1);
	while (cmd[i] != NULL)
	{
		if (!ft_strcmp(cmd[i], "<") || !ft_strcmp(cmd[i], "<<"))
			last_index = i;
		i++;
	}
	return (last_index);
}

void	handle_infiles(char **cmd, t_env *env, int status)
{
	int		i;
	int		fd;

	i = get_infiles_index(cmd);
	if (i == -1)
		return ;
	if (check_infiles(cmd) == 1)
	{
		fd = open(cmd[i + 1], O_RDONLY);
		if (fd == -1)
		{
			perror("minishell : open");
			return ;
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (check_infiles(cmd) == 2)
		handle_heredoc(cmd, status);
	if (status == 0)
		check_functions(cmd + 2, env, 2);
	else
		check_functions(cmd + 2, env, 1);
	if (status == 1)
		dup2(1, STDIN_FILENO);
	if (check_infiles(cmd) == 2)
		unlink(".heredoc");
}

void	handle_heredoc(char **cmd, int status)
{
	int		i;
	int		fd[2];
	char	*line;

	i = get_infiles_index(cmd);
	if (i == -1)
		return ;
	if (check_infiles(cmd) == 2)
	{
		if (pipe(fd) == -1)
		{
			perror("minishell : pipe");
			return ;
		}
		if (status)
		{
			while (1)
			{
				ft_putstr_fd(">", 1);
				line = get_next_line(0);
				if (!ft_strncmp(cmd[i + 1], line, ft_strlen(line) - 2))
					break ;
				ft_putstr_fd(line, fd[1]);
			}
		}
		close(fd[1]);
		if (status == 1)
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}
