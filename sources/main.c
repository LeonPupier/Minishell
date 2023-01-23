/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:30:34 by lpupier           #+#    #+#             */
/*   Updated: 2023/01/23 16:39:17 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*msg;
	char	*line;
	char	**cmd;

	(void)argc;
	(void)argv;
	msg = ft_strjoin(ft_strjoin(ft_strdup("\e[1;94;40m"), \
	get_env(envp, "USER")), ft_strdup("@minishell\e[0m\e[1;91;40m ➜\e[0m "));
	signal(SIGINT, signal_ctrl_c);
	using_history();
	while (1)
	{
		line = readline(msg);
		if (!line)
		{
			printf("exit\n");
			line = ft_strdup("exit");
		}
		if (line[0] != '\0')
		{
			add_history(line);
			cmd = verify_args(ft_split(line, ' '), envp);
			if (!ft_strncmp(cmd[0], "echo", 4))
				echo(cmd);
			else if (!ft_strncmp(cmd[0], "pwd", 3))
				pwd(cmd, envp);
			else if (!ft_strncmp(cmd[0], "env", 3))
				env(cmd, envp);
			else if (!ft_strncmp(cmd[0], "export", 6))
				ft_export(cmd, &envp);
			else if (!ft_strncmp(cmd[0], "exit", 4))
			{
				free_tab(cmd);
				free(line);
				break ;
			}
			else
				printf("%s\e[31m: Command not found.\e[0m\n", cmd[0]);
			free_tab(cmd);
		}
		free(line);
	}
	free(msg);
	return (EXIT_SUCCESS);
}
