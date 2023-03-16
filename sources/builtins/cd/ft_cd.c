/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:14:36 by vcart             #+#    #+#             */
/*   Updated: 2023/03/16 16:59:47 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	update_pwd(t_list *new_envp)
{
	char	cwd[1024];
	char	*cmd[3];
	char	*pwd;
	char	*wd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror("getcwd"), 1);
	cmd[0] = "export";
	pwd = ft_strdup("PWD=");
	if (!pwd)
		return (1);
	wd = ft_strdup(cwd);
	if (!wd)
	{
		free(pwd);
		return (1);
	}
	cmd[1] = ft_strjoin(pwd, wd);
	if (!cmd[1])
		return (free(pwd), free(wd), 1);
	cmd[2] = NULL;
	ft_export(cmd, new_envp);
	free(cmd[1]);
	return (0);
}

int	cd(char **cmd, t_list *new_envp, char **envp)
{
	int		argc;
	char	*home;

	argc = get_array_size(cmd);
	if (argc == 1)
	{
		home = get_env(envp, "HOME");
		if (chdir(home) != 0)
			perror("cd");
		free(home);
	}
	else if (argc > 2)
		return (printf("cd : too many arguments\n"), 1);
	else if (chdir(cmd[1]) != 0)
		return (perror("cd"), 1);
	return (update_pwd(new_envp));
}
