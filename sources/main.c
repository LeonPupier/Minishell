/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:30:34 by lpupier           #+#    #+#             */
/*   Updated: 2023/01/24 14:37:50 by lpupier          ###   ########.fr       */
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
	pid_t	id;

	(void)argc;
	(void)argv;
	printf("Welcome to Minishell by lpupier and vcart !\n");
	msg = ft_strjoin(ft_strjoin(ft_strdup("\e[1;94;40m"), \
	get_env(envp, "USER")), ft_strdup("@minishell\e[0m\e[1;91;40m ➜\e[0m "));
	signal(SIGINT, signal_ctrl_c);
	using_history();
	while (1)
	{
		prompt = readline(msg);
		if (!prompt)
		{
			printf("exit\n");
			prompt = ft_strdup("exit");
		}
		if (prompt[0] != '\0')
		{
			add_history(prompt);
			cmd = verify_args(ft_split(prompt, ' '), envp);
			if (!ft_strcmp(cmd[0], "echo"))
				echo(cmd);
			else if (!ft_strcmp(cmd[0], "pwd"))
				pwd(cmd, envp);
			else if (!ft_strcmp(cmd[0], "env"))
				env(cmd, envp);
			else if (!ft_strcmp(cmd[0], "export"))
				ft_export(cmd, &envp);
			else if (!ft_strcmp(cmd[0], "exit"))
			{
				free_tab(cmd);
				free(prompt);
				break ;
			}
			else if (!ft_strcmp(cmd[0], "deep"))
				printf("Level: %s\n", getenv("SHLVL"));
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
	free(msg);
	return (EXIT_SUCCESS);
}
