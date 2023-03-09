/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:30:34 by lpupier           #+#    #+#             */
/*   Updated: 2023/03/09 13:12:01 by lpupier          ###   ########.fr       */
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
	env->new_envp = new_envp;
	loop_main(prompt, env);
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
	return (ft_strjoin(ft_strjoin(ft_strdup("\e[1;94;40m"), \
	get_env(envp, "USER")), ft_strdup("@minishell\e[0m\e[1;91;40m ➜\e[0m ")));
}

int	loop_main(char *prompt, t_env *env)
{
	int		pipe;
	int		idx;
	char	*command;
	char	**cmds_pipe;
	char	***cmds;

	while (1)
	{
		env->envp = list_to_envp(env->new_envp);
		command = readline(prompt);
		if (!command)
			return (printf("exit\n"), 0);
		if (command[0] != '\0')
		{
			add_history(command);
			pipe = contains(command, '|');
			cmds_pipe = ft_split(command, '|');
			cmds = malloc(sizeof(char **) * (get_array_size(cmds_pipe) + 1));
			if (!cmds)
				return (free(command), free_tab(cmds_pipe), 1);
			cmds[get_array_size(cmds_pipe)] = NULL;
			idx = -1;
			while (cmds_pipe[++idx])
			{
				cmds[idx] = malloc(sizeof(char *));
				cmds[idx][0] = NULL;
				cmds[idx] = cmd_parsing(cmds[idx], cmds_pipe[idx], env->envp);
				if (!cmds[idx])
					return (free(command), free_tab(cmds_pipe), free_2tab(cmds), 1);
				if (!pipe && check_functions(cmds[idx], env, 0) == EXIT_FAILURE)
					return (free(command), free_tab(cmds_pipe), free_2tab(cmds), 0);
			}
			if (pipe)
				ft_pipe(cmds, env);
			free_tab(cmds_pipe);
			free_2tab(cmds);
		}
		free_tab(env->envp);
		free(command);
	}
}
