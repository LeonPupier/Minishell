/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:30:34 by lpupier           #+#    #+#             */
/*   Updated: 2023/03/13 13:34:00 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	t_list	*new_envp;
	t_env	*env;

	prompt = init_minishell(argc, argv, envp);
	new_envp = envp_to_list(envp);
	env = malloc(sizeof(t_env));
	if (!env)
		return (free(prompt), free_list(new_envp), EXIT_FAILURE);
	env->new_envp = new_envp;
	loop_main(prompt, env);
	free_list(env->new_envp);
	free_tab(env->envp);
	free(env);
	free(prompt);
	return (EXIT_SUCCESS);
}

char	*init_minishell(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, signal_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	using_history();
	minishell_header();
	return (ft_strjoin(ft_strjoin(ft_strdup("\001\e[1;94;40m\002"), \
	get_env(envp, "USER")), \
	ft_strdup("@minishell\001\e[0m\002\001\e[1;91;40m\002 \001➜\002\001\e[0m\002 ")));
}

int	loop_main(char *prompt, t_env *env)
{
	char	*command;

	while (1)
	{
		env->envp = list_to_envp(env->new_envp);
		command = readline(prompt);
		if (!command)
			return (printf("exit\n"), 0);
		if (command[0] != '\0')
		{
			add_history(command);
			if (!command_interpretation(command, env))
				return (free(command), 0);
		}
		free_tab(env->envp);
		free(command);
	}
	return (1);
}

int	command_interpretation(char *command, t_env *env)
{
	int		pipe;
	int		status;
	char	**cmds_pipe;
	char	***cmds;

	pipe = contains(command, '|');
	cmds_pipe = ft_split(command, '|');
	if (!cmds_pipe)
		return (0);
	cmds = malloc(sizeof(char **) * (get_array_size(cmds_pipe) + 1));
	if (!cmds)
		return (free_tab(cmds_pipe), 1);
	cmds[get_array_size(cmds_pipe)] = NULL;
	status = shell_core(cmds_pipe, cmds, pipe, env);
	return (free_tab(cmds_pipe), free_2tab(cmds), status);
}

int	shell_core(char **cmds_pipe, char ***cmds, int pipe, t_env *env)
{
	int	idx;

	idx = -1;
	while (cmds_pipe[++idx])
	{
		cmds[idx] = malloc(sizeof(char *));
		if (!cmds[idx])
			return (0);
		cmds[idx][0] = NULL;
		cmds[idx] = cmd_parsing(cmds[idx], cmds_pipe[idx], env->envp);
		if (!cmds[idx])
			return (1);
		if (!pipe && check_functions(cmds[idx], env, 0) == EXIT_FAILURE)
			return (0);
	}
	if (pipe)
		ft_pipe(cmds, env);
	return (1);
}
