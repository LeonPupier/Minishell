/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:30:34 by lpupier           #+#    #+#             */
/*   Updated: 2023/01/20 15:40:14 by lpupier          ###   ########.fr       */
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
	msg = ft_strjoin(ft_strjoin("\e[1;94;40m", get_env(envp, "USER")), \
	"@minishell\e[0m\e[1;91;40m ➜\e[0m ");
	using_history();
	while (1)
	{
		line = readline(msg);
		if (!line)
			return (free(msg), printf("\n\e[31m[READ ERROR]\e[0m\n"), EXIT_FAILURE);
		if (line[0] != '\0')
		{
			add_history(line);
			cmd = verify_args(ft_split(line, ' '), envp);
			if (!ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])))
				echo(cmd);
			else if (!ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])))
				pwd(cmd, envp);
			else if (!ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])))
				env(cmd, envp);
			else if (!ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])))
				ft_export(cmd, &envp);
			else if (!ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])))
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
