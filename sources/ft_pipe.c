/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:16:45 by vcart             #+#    #+#             */
/*   Updated: 2023/02/20 15:18:14 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int exec_first_cmd(int *fd, char **cmd_1, char **envp, t_list *new_envp)
{
	int fd_infile;

	fd_infile = open(cmd_1[1], O_RDONLY);
	if (fd_infile == -1)
		return(perror(cmd_1[0]), -1);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd_infile, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd_infile);
	check_functions(cmd_1, envp, new_envp);
	return (0);
}

int exec_second_cmd(int *fd, char **cmd_2, char **envp, t_list *new_envp)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	check_functions(cmd_2, envp, new_envp);
	return (0);
}

int ft_pipe(char ***cmd_tab, char **envp, t_list *new_envp)
{
	int fd[2];
	int pid1;
	int pid2;

	if (pipe(fd) == -1)
		return (-1);
	pid1 = fork();
	if (pid1 < 0)
		return (-2);
	if (pid1 == 0)
	{
		if (exec_first_cmd(fd, cmd_tab[0], envp, new_envp) == -1)
			exit(1);
		exit(0);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (-2);
	if (pid2 == 0)
	{
		if (exec_second_cmd(fd, cmd_tab[1], envp, new_envp) == -1)
			exit(1);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
