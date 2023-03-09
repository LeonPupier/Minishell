/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 21:19:19 by lpupier           #+#    #+#             */
/*   Updated: 2023/03/09 13:44:20 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_functions(char **cmd, t_env *envi, int status)
{
	char	*path;
	int		builtins_exit;

	if (!status && check_redirections(cmd))
		make_redirections(cmd);
	if (status == 2)
		return (1);
	builtins_exit = check_builtins(cmd, envi);
	if (builtins_exit == -1)
		return (EXIT_FAILURE);
	if (builtins_exit == 0)
	{
		path = get_binary_path(cmd[0], envi->envp);
		if (waitpid(binary(path, cmd, envi->envp), \
			NULL, 0) == -1)
			printf("\e[31m[ERROR]: %s\e[0m\n", cmd[0]);
		free(path);
	}
	if (!status && check_redirections(cmd))
		dup2(0, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int	check_builtins(char **cmd, t_env *envi)
{
	if (!ft_strcmp(cmd[0], "echo"))
		echo(cmd);
	else if (!ft_strcmp(cmd[0], "pwd"))
		pwd(cmd, envi->envp);
	else if (!ft_strcmp(cmd[0], "env"))
		env(cmd, envi->envp);
	else if (!ft_strcmp(cmd[0], "cd"))
		cd(cmd, envi->new_envp, envi->envp);
	else if (!ft_strcmp(cmd[0], "export"))
		ft_export(cmd, envi->new_envp);
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(cmd, envi->new_envp);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (printf("exit\n"), -1);
	else if (!ft_strcmp(cmd[0], "<") || !ft_strcmp(cmd[0], "<<"))
		handle_infiles(cmd, envi, 1);
	else
		return (0);
	return (1);
}
