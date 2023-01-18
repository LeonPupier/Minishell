/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:01:05 by vcart             #+#    #+#             */
/*   Updated: 2023/01/18 14:52:17 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	exec_first_cmd(int	*fd, char **argv, char **envp)
{
	char	**args;
	char	*path;
	int		fd_infile;

	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
		return (-1);
	dup2(fd[1], STDOUT_FILENO);
	dup2(fd_infile, STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(fd_infile);
	args = ft_split(argv[2], ' ');
	path = get_binary_path(args[0], envp);
	if (path == NULL)
		return (-1);
	execve(path, args, envp);
	free_args(args);
	return (free(path), -1);
}

int	exec_second_cmd(int	*fd, char **argv, char **envp)
{
	int		file;
	char	*path;
	char	**args;

	file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
		return (-1);
	dup2(fd[0], STDIN_FILENO);
	dup2(file, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(file);
	args = ft_split(argv[3], ' ');
	path = get_binary_path(args[0], envp);
	if (path == NULL)
		return (-1);
	execve(path, args, envp);
	free_args(args);
	return (free(path), -1);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (argc != 5)
		return (-1);
	if (pipe(fd) == -1)
		return (-1);
	pid1 = fork();
	if (pid1 < 0)
		return (-2);
	if (pid1 == 0)
		if (exec_first_cmd(fd, argv, envp) == -1)
			return (-3);
	pid2 = fork();
	if (pid2 < 0)
		return (-2);
	if (pid2 == 0)
		if (exec_second_cmd(fd, argv, envp) == -1)
			return (-3);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
