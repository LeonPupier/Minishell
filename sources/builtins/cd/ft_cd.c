/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:14:36 by vcart             #+#    #+#             */
/*   Updated: 2023/02/22 08:48:25 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	update_pwd(t_list *new_envp)
{
	char	cwd[1024];
	char	*cmd[3];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd");
	cmd[0] = "export";
	cmd[1] = ft_strjoin(ft_strdup("PWD="), ft_strdup(cwd));
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
