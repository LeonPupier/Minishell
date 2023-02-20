/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart < vcart@student.42lyon.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:30:34 by lpupier           #+#    #+#             */
/*   Updated: 2023/02/20 15:10:08 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_functions(char **cmd, char **envp, t_list *new_envp)
{
	char	*path;

	if (!ft_strcmp(cmd[0], "echo"))
		echo(cmd);
	else if (!ft_strcmp(cmd[0], "pwd"))
		pwd(cmd, envp);
	else if (!ft_strcmp(cmd[0], "env"))
		env(cmd, envp);
	else if (!ft_strcmp(cmd[0], "cd"))
		cd(cmd, new_envp, envp);
	else if (!ft_strcmp(cmd[0], "export"))
		ft_export(cmd, new_envp);
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(cmd, new_envp);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (printf("exit\n"), EXIT_FAILURE);
	else
	{
		path = get_binary_path(cmd[0], envp);
		if (waitpid(binary(path, cmd, envp), \
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

	(void)argc;
	(void)argv;
	printf("Welcome to Minishell by lpupier and vcart !\n");
	msg = ft_strjoin(ft_strjoin(ft_strdup("\e[1;94;40m"), \
	get_env(envp, "LOGNAME")), ft_strdup("@minishell\e[0m\e[1;91;40m ➜\e[0m "));
	signal(SIGINT, signal_ctrl_c);
	signal(SIGQUIT, signal_ctrl_backslash);
	using_history();
	new_envp = envp_to_list(envp);
	while (1)
	{
		envp = list_to_envp(new_envp);
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
				cmds[idx] = parsing(cmds[idx], cmds_pipe[idx], envp);
				if (!pipe && check_functions(cmds[idx], envp, new_envp) == EXIT_FAILURE)
					return (free(prompt), free(msg), EXIT_SUCCESS);
			}
			if (pipe)
				ft_pipe(cmds, envp, new_envp);
			free_tab(cmds_pipe);
		}
		free(prompt);
	}
	return (EXIT_SUCCESS);
}
