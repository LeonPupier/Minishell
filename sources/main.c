/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:30:34 by lpupier           #+#    #+#             */
/*   Updated: 2023/02/13 12:11:17 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_functions(char **cmd, char **envp, t_list *new_envp)
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
			NULL, WUNTRACED | WCONTINUED) == -1)
			printf("\e[31m[ERROR]: %s\e[0m\n", cmd[0]);
		free(path);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	char	*msg;
	char	*prompt;
	char	**cmd;
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
			return (printf("exit\n"), free_tab(cmd), free(msg), EXIT_SUCCESS);
		if (prompt[0] != '\0')
		{
			add_history(prompt);
			cmd = malloc(sizeof(char *));
			cmd[0] = NULL;
			cmd = quotes_variables_interpretation(cmd, prompt, envp);
			if (check_functions(cmd, envp, new_envp) == EXIT_FAILURE)
				return (free(prompt), free(msg), free_tab(cmd), EXIT_SUCCESS);
			free_tab(cmd);
		}
		free(prompt);
	}
	return (EXIT_SUCCESS);
}
