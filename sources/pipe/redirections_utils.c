/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:24:56 by vcart             #+#    #+#             */
/*   Updated: 2023/02/28 13:35:26 by vcart            ###   ########.fr       */
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
	int		i;
	int		fd;
	char	**command;

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
	}
	command = malloc(sizeof(char *));
	command[0] = cmd[i + 2];
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (status == 0)
		check_functions(command, env, 2);
	else
		check_functions(command, env, 1);
	if (status == 1)
		dup2(1, STDIN_FILENO);
	free(command);
}

void	handle_heredoc(char **cmd, t_env *env)
{
	int		i;
	t_list	*here_doc;
	char	**command;
	int		fd[2];

	i = get_infiles_index(cmd);
	if (i == -1)
		return ;
	if (check_infiles(cmd) == 2)
	{
		here_doc = NULL;
		while (1)
		{
			if (!ft_strcmp(cmd[i + 1], get_next_line(0)))
				break ;
			ft_lstadd_back(&here_doc, ft_lstnew(get_next_line(0)));
		}
		if (pipe(fd) == -1)
			perror("minishell : pipe");
		while (here_doc != NULL)
		{
			ft_putchar_fd('>', 1);
			ft_putstr_fd(here_doc->content, fd[0]);
			here_doc = here_doc->next;
		}
		close(fd[0]);
		close(fd[1]);
		command = malloc(sizeof(char *));
		command[0] = cmd[i + 2];
		dup2(fd[0], STDIN_FILENO);
		check_functions(command, env, 1);
	}
}

void	handle_all_infiles(char **cmd, t_env *env, int status)
{
	if (check_infiles(cmd) == 1)
		handle_infiles(cmd, env, status);
	else if (check_infiles(cmd) == 2)
		handle_heredoc(cmd, env);
	return ;
}