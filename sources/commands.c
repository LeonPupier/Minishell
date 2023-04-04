/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 21:19:19 by lpupier           #+#    #+#             */
/*   Updated: 2023/04/04 10:48:32 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Global_variable: exit status code
int	g_exit_status;

int	check_functions(char **cmd, t_env *envi, int status)
{
	int		builtins_exit;

	if (!cmd || !cmd[0])
		return (EXIT_SUCCESS);
	if (check_infiles(cmd))
	{
		if (handle_infiles(cmd, envi, 1) == -2)
			return (EXIT_SUCCESS);
	}
	else if (check_redirections(cmd))
	{
		envi->fd_out = make_redirections(cmd);
		if (envi->fd_out == -1)
			return (EXIT_SUCCESS);
	}
	if (!check_infiles(cmd))
	{
		builtins_exit = check_builtins(cmd, envi, &g_exit_status);
		if (builtins_exit == -1)
			return (EXIT_FAILURE);
		if (builtins_exit == 0)
		{
			if (launch_program(cmd, status, envi) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		if (!status)
		{
			if (dup2(0, STDOUT_FILENO) == -1)
				return (EXIT_FAILURE);
			envi->fd_in = 1;
		}
	}
	if (envi->fd_in != 0)
	{
		close(envi->fd_in);
		envi->fd_in = 0;
		dup2(1, envi->fd_in);
	}
	if (envi->fd_out != 1)
	{
		close(envi->fd_out);
		envi->fd_out = 1;
		dup2(0, envi->fd_out);
	}
	return (EXIT_SUCCESS);
}

int	check_builtins(char **cmd, t_env *envi, int *exit_status)
{
	if (!ft_strcmp(cmd[0], "echo"))
		*exit_status = echo(cmd);
	else if (!ft_strcmp(cmd[0], "pwd"))
		*exit_status = pwd(cmd);
	else if (!ft_strcmp(cmd[0], "env"))
		*exit_status = env(cmd, envi->new_envp);
	else if (!ft_strcmp(cmd[0], "cd"))
		*exit_status = cd(cmd, envi);
	else if (!ft_strcmp(cmd[0], "export"))
		*exit_status = ft_export(cmd, envi->new_envp);
	else if (!ft_strcmp(cmd[0], "unset"))
		*exit_status = ft_unset(cmd, envi->new_envp);
	else if (!ft_strcmp(cmd[0], "exit"))
	{
		*exit_status = ft_exit(cmd);
		if (*exit_status != -1)
			return (-1);
	}
	else
		return (*exit_status = 127, 0);
	return (1);
}

int	launch_program(char **cmd, int status, t_env *envi)
{
	char	*path;
	int		child_status;

	path = get_binary_path(cmd[0], envi->envp);
	if (!path)
		return (EXIT_FAILURE);
	if (waitpid(binary(path, cmd, envi->envp), &child_status, 0) == -1)
		printf("\e[31m[ERROR]: %s\e[0m\n", cmd[0]);
	free(path);
	if (!status && check_redirections(cmd))
	{
		if (dup2(0, STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
		envi->fd_in = 1;
	}
	g_exit_status = WEXITSTATUS(child_status);
	return (EXIT_SUCCESS);
}

int	get_exit_status(void)
{
	return (g_exit_status);
}

void	set_exit_status(int code)
{
	g_exit_status = code;
}
