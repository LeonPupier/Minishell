/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:30:34 by lpupier           #+#    #+#             */
/*   Updated: 2023/01/18 17:08:08 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_env(char **envp, char *request)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], request, ft_strlen(request)) == 0)
			return (ft_strdup(envp[i] + ft_strlen(request) + 1));
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*msg;
	char	**cmd;

	(void)argc;
	(void)argv;
	msg = ft_strjoin("\e[1;94;40m", get_env(envp, "USER"));
	msg = ft_strjoin(msg, "@minishell\e[0m\e[1;91;40m ➜\e[0m ");
	using_history();
	while (1)
	{
		line = readline(msg);
		if (!line)
			return (printf("\e[31m[Error] Readline error.\e[0m\n"), EXIT_FAILURE);
		if (line[0] == '\0')
			continue ;
		add_history(line);
		cmd = ft_split(line, ' ');
		if (!ft_strncmp(cmd[0], "echo", 4))
		{
			if (ft_strncmp(cmd[1], "-n", 2))
			{
				skip_whitespace(line);
				printf("%s\n", line + ft_strlen(cmd[0]) + 1);
			}
			else
			{
				skip_whitespace(line);
				printf("%s", line + ft_strlen(cmd[0]) + 4);
			}
		}
		if (!ft_strncmp(line, "exit", ft_strlen(line)))
			return (EXIT_SUCCESS);
	}
}