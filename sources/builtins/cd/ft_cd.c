/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:14:36 by vcart             #+#    #+#             */
/*   Updated: 2023/03/10 10:35:04 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	update_pwd(t_list *new_envp)
{
	char	cwd[1024];
	char	*cmd[3];
	char	*pwd;
	char	*wd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd");
	cmd[0] = "export";
	pwd = ft_strdup("PWD=");
	if (!pwd)
		return ;
	wd = ft_strdup(cwd);
	if (!wd)
	{
		free(pwd);
		return ;
	}
	cmd[1] = ft_strjoin(pwd, wd);
	if (!cmd[1])
	{
		free(pwd);
		free(wd);
		return ;
	}
	cmd[2] = NULL;
	ft_export(cmd, new_envp);
}

void	cd(char **cmd, t_list *new_envp, char **envp)
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
		printf("cd : too many arguments\n");
	else if (chdir(cmd[1]) != 0)
		perror("cd");
	update_pwd(new_envp);
}
