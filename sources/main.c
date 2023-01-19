/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:30:34 by lpupier           #+#    #+#             */
/*   Updated: 2023/01/19 18:16:01 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*msg;
	char	**cmd;

	(void)argc;
	(void)argv;
	msg = ft_strjoin("\e[1;94;40m", getenv("USER"));
	msg = ft_strjoin(msg, "@minishell\e[0m\e[1;91;40m ➜\e[0m ");
	using_history();
	while (1)
	{
		line = readline(msg);
		if (!line)
			return (free(msg), printf("\n\e[31m[READ ERROR]\e[0m\n"), EXIT_FAILURE);
		if (line[0] != '\0')
		{
			add_history(line);
			cmd = ft_split(line, ' ');
			cmd = replace_var(cmd);
			if (!ft_strncmp(cmd[0], "echo", INT_MAX))
				echo(cmd);
			else if (!ft_strncmp(cmd[0], "pwd", INT_MAX))
				pwd(cmd);
			else if (!ft_strncmp(cmd[0], "env", INT_MAX))
				env(cmd, envp);
			else if (!ft_strncmp(cmd[0], "export", INT_MAX))
				ft_export(cmd, envp);
			else if (!ft_strncmp(cmd[0], "exit", INT_MAX))
			{
				free(line);
				free_tab(cmd);
				break ;
			}
			else
				printf("\e[31mCommand not found:\e[0m %s\n", cmd[0]);
			free_tab(cmd);
		}
		free(line);
	}
	free(msg);
	return (EXIT_SUCCESS);
}
