/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:30:34 by lpupier           #+#    #+#             */
/*   Updated: 2023/03/06 10:25:45 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
				if (!pipe && check_functions(cmds[idx], env, 0) == EXIT_FAILURE)
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
