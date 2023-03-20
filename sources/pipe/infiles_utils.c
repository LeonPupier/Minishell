/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcart <vcart@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:28:37 by vcart             #+#    #+#             */
/*   Updated: 2023/03/20 15:34:53 by vcart            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_with_pipes(char **cmd, int i, t_env *env)
{
	char	**trunc_cmd;

	if (i > 0 && check_infiles(cmd) == 1)
	{
		trunc_cmd = ignore_infile(cmd);
		if (!trunc_cmd)
			return ;
		check_functions(trunc_cmd, env, 1);
		free(trunc_cmd);
	}
	else if (i > 0 && check_infiles(cmd) == 2)
	{
		trunc_cmd = ignore_heredoc(cmd);
		check_functions(trunc_cmd, env, 1);
		free(trunc_cmd);
	}
	else
		check_functions(cmd + 2, env, 1);
	dup2(1, STDIN_FILENO);
}

void	create_heredoc(char **cmd, int i, int fd[2])
{
	char	*line;

	while (1)
	{
		ft_putstr_fd(">", 0);
		line = get_next_line(0);
		if (!ft_strncmp(cmd[i + 1], line, ft_strlen(cmd[i + 1])))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
}
