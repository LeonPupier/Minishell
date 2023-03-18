/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 21:19:19 by lpupier           #+#    #+#             */
/*   Updated: 2023/03/18 14:55:27 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Global_variable: exit status code
int	g_exit_status;

int	check_functions(char **cmd, t_env *envi, int status)
{
	char	*path;
	int		builtins_exit;
	int		child_status;

	if (!status && check_redirections(cmd))
		make_redirections(cmd);
	builtins_exit = check_builtins(cmd, envi, &g_exit_status);
	if (builtins_exit == -1)
		return (EXIT_FAILURE);
	if (builtins_exit == 0)
	{
		path = get_binary_path(cmd[0], envi->envp);
		if (waitpid(binary(path, cmd, envi->envp), &child_status, 0) == -1)
			printf("\e[31m[ERROR]: %s\e[0m\n", cmd[0]);
		free(path);
		if (!status && check_redirections(cmd))
			dup2(0, STDOUT_FILENO);
		g_exit_status = WEXITSTATUS(child_status);
	}
	return (EXIT_SUCCESS);
}

int	check_builtins(char **cmd, t_env *envi, int *exit_status)
{
	if (check_infiles(cmd))
		handle_infiles(cmd, envi, 1);
	else if (!ft_strcmp(cmd[0], "echo"))
		*exit_status = echo(cmd);
	else if (!ft_strcmp(cmd[0], "pwd"))
		*exit_status = pwd(cmd, envi->envp);
	else if (!ft_strcmp(cmd[0], "env"))
		*exit_status = env(cmd, envi->new_envp);
	else if (!ft_strcmp(cmd[0], "cd"))
		*exit_status = cd(cmd, envi->new_envp, envi->envp);
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

int	get_exit_status(void)
{
	return (g_exit_status);
}
