/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:30:34 by lpupier           #+#    #+#             */
/*   Updated: 2023/02/24 11:33:14 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_functions(char **cmd, t_env *envi)
{
	char	*path;

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
		return (printf("exit\n"), EXIT_FAILURE);
	else
	{
		path = get_binary_path(cmd[0], envi->envp);
		if (waitpid(binary(path, cmd, envi->envp), \
			NULL, 0) == -1)
			printf("\e[31m[ERROR]: %s\e[0m\n", cmd[0]);
		free(path);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	char	*msg;
	char	*prompt;
	char	**cmds_pipe;
	char	***cmds;
	int		idx;
	int		pipe;
	t_list	*new_envp;
	t_env	*env;

	(void)argc;
	(void)argv;
	minishell_header();
	new_envp = envp_to_list(envp);
	env = malloc(sizeof(t_env));
	env->envp = envp;
	env->new_envp = new_envp;
	msg = ft_strjoin(ft_strjoin(ft_strdup("\e[1;94;40m"), \
	get_env(env->envp, "USER")), ft_strdup("@minishell\e[0m\e[1;91;40m ➜\e[0m "));
	signal(SIGINT, signal_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	using_history();
	while (1)
	{
		env->envp = list_to_envp(env->new_envp);
		prompt = readline(msg);
		if (!prompt)
			return (free(msg), EXIT_SUCCESS);
		pipe = contains(prompt, '|');
		if (prompt[0] != '\0')
		{
			add_history(prompt);
			cmds_pipe = ft_split(prompt, '|');
			cmds = malloc(sizeof(char **) * (get_array_size(cmds_pipe) + 1));
			if (!cmds)
				return (free_tab(cmds_pipe), free(msg), EXIT_FAILURE);
			cmds[get_array_size(cmds_pipe)] = NULL;
			idx = -1;
			while (cmds_pipe[++idx])
			{
				cmds[idx] = malloc(sizeof(char *));
				cmds[idx][0] = NULL;
				cmds[idx] = cmd_parsing(cmds[idx], cmds_pipe[idx], env->envp);
				if (!pipe && check_functions(cmds[idx], env) == EXIT_FAILURE)
					return (free(prompt), free(msg), EXIT_SUCCESS);
			}
			if (pipe)
				ft_pipe(cmds, env);
			free_tab(cmds_pipe);
		}
		free(prompt);
	}
	return (EXIT_SUCCESS);
}
