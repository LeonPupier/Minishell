/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:24:56 by vcart             #+#    #+#             */
/*   Updated: 2023/03/23 11:14:59 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	handle_infiles(char **cmd, t_env *env, int status)
{
	int		i;

	i = get_infiles_index(cmd);
	if (i == 0 && cmd[i + 1] == NULL)
		return (perror("minishell : syntax error near unexpected\
		token `newline'"), -2);
	if (check_infiles(cmd) == 1)
	{
		if (open_infile(cmd, i) == -2)
			return (-2);
	}
	else if (check_infiles(cmd) == 2)
	{
		if (handle_heredoc(cmd, status) == -1)
			return (-2);
	}
	if (status == 1)
	{
		if (handle_with_pipes(cmd, i, env) == -1)
			return (-2);
	}
	return (1);
}

int	handle_heredoc(char **cmd, int status)
{
	int		i;
	int		fd[2];

	i = get_infiles_index(cmd);
	if (i == -1)
		return (-1);
	if (check_infiles(cmd) == 2)
	{
		if (pipe(fd) == -1)
			return (perror("minishell : pipe"), -1);
		if (status)
		{
			if (create_heredoc(cmd, i, fd) == -1)
				return (-1);
		}
		close(fd[1]);
		if (status == 1)
		{
			if (dup2(fd[0], STDIN_FILENO) == -1)
				return (-1);
		}
		close(fd[0]);
	}
	return (0);
}
