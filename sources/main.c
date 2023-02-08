/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:30:34 by lpupier           #+#    #+#             */
/*   Updated: 2023/02/08 19:50:58 by lpupier          ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char	*msg;
	char	*prompt;
	char	**cmd;
	char	*path;
	t_list	*new_envp;
	pid_t	id;

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
			cmd = find_occurrence(cmd, prompt, '"');
			retrieve_environment_variables(cmd, envp);
			if (!ft_strcmp(cmd[0], "echo"))
				echo(cmd);
			else if (!ft_strcmp(cmd[0], "pwd"))
				pwd(cmd, envp);
			else if (!ft_strcmp(cmd[0], "env"))
				env(cmd, envp);
			else if (!ft_strcmp(cmd[0], "export"))
				ft_export(cmd, new_envp);
			else if (!ft_strcmp(cmd[0], "unset"))
				ft_unset(cmd, new_envp);
			else if (!ft_strcmp(cmd[0], "exit"))
				return (free(prompt), free_tab(cmd), free(msg), EXIT_SUCCESS);
			else
			{
				path = get_binary_path(cmd[0], envp);
				id = binary(path, cmd, envp);
				free(path);
				if (waitpid(id, NULL, WUNTRACED | WCONTINUED) == -1)
					printf("\e[31m[ERROR]: %s\e[0m\n", cmd[0]);
			}
			free_tab(cmd);
		}
		free(prompt);
	}
	return (EXIT_SUCCESS);
}
