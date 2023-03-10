/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:24:56 by vcart             #+#    #+#             */
/*   Updated: 2023/03/13 13:35:30 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	**ignore_infile(char **cmd)
{
	int		i;
	int		j;
	char	**new_cmd;

	i = 0;
	j = 0;
	new_cmd = malloc(sizeof(char *) * (get_array_size(cmd) + 1));
	if (!new_cmd)
		return (NULL);
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], "<"))
		{
			new_cmd[j] = ft_strdup(cmd[i]);
			if (!new_cmd[j])
				return (free_tab(new_cmd), NULL);
			j++;
		}
		else if (cmd[i + 2])
			i++;
		i++;
	}
	new_cmd[j] = NULL;
	return (new_cmd);
}

char	**ignore_heredoc(char **cmd)
{
	int		i;
	char	**new_cmd;

	i = get_infiles_index(cmd);
	new_cmd = malloc(sizeof(char *) * 2);
	if (!new_cmd)
		return (NULL);
	new_cmd[0] = ft_strdup(cmd[i - 1]);
	if (!new_cmd[0])
		return (free(new_cmd), NULL);
	new_cmd[1] = NULL;
	return (new_cmd);
}

void	handle_infiles(char **cmd, t_env *env, int status)
{
	int		i;
	int		fd;
	char	**trunc_cmd;

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
	if (status == 1)
	{
		if (i > 0 && check_infiles(cmd) == 1)
		{
			trunc_cmd = ignore_infile(cmd);
			if (!trunc_cmd)
				return ;
			check_functions(trunc_cmd, env, 1);
			free(trunc_cmd);
		}
		else if (i > 0 && check_infiles(cmd) == 2)
		{
			trunc_cmd = ignore_heredoc(cmd);
			check_functions(trunc_cmd, env, 1);
			free(trunc_cmd);
		}
		else
			check_functions(cmd + 2, env, 1);
		dup2(1, STDIN_FILENO);
	}
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
				ft_putstr_fd(">", 0);
				line = get_next_line(0);
				if (!ft_strncmp(cmd[i + 1], line, ft_strlen(cmd[i + 1])))
				{
					free(line);
					break ;
				}
				ft_putstr_fd(line, fd[1]);
				free(line);
			}
		}
		close(fd[1]);
		if (status == 1)
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}
