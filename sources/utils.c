/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart < vcart@student.42lyon.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:26:01 by lpupier           #+#    #+#             */
/*   Updated: 2023/02/20 12:58:02 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

pid_t	binary(const char *program, char **args, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		return (pid);
	else
	{
		if (execve(program, args, envp) == -1)
			printf("%s\e[31m: Command not found.\e[0m\n", args[0]);
		exit(EXIT_FAILURE);
	}
}

int	is_in_envp(char **envp, char *request)
{
	int		i;
	char	**env_split;

	i = 0;
	while (envp[i])
	{
		env_split = ft_split(envp[i], '=');
		if (!ft_strcmp(env_split[0], request))
			return (free_tab(env_split), 1);
		free_tab(env_split);
		i++;
	}
	return (0);
}

char	*get_env(char **envp, char *request)
{
	int		i;
	char	**env_split;
	char	*result;

	i = 0;
	if (!is_in_envp(envp, request))
		return (NULL);
	while (envp[i])
	{
		env_split = ft_split(envp[i], '=');
		if (!ft_strcmp(env_split[0], request))
		{
			result = ft_strdup(env_split[1]);
			return (free_tab(env_split), result);
		}
		free_tab(env_split);
		i++;
	}
	return (NULL);
}

char	*get_binary_path(char *cmd, char **envp)
{
	char	**path_list;
	char	*path;
	char	*result;
	char	*env;
	int		i;

	env = get_env(envp, "PATH");
	path_list = ft_split(env, ':');
	free(env);
	i = -1;
	while (path_list[++i])
	{
		path = ft_strjoin(ft_strdup(path_list[i]), ft_strdup("/"));
		result = ft_strjoin(path, ft_strdup(cmd));
		if (access(result, F_OK | X_OK) == 0)
			return (free_tab(path_list), result);
		free(result);
	}
	free_tab(path_list);
	return (ft_strdup(cmd));
}
