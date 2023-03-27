/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:28:37 by vcart             #+#    #+#             */
/*   Updated: 2023/03/27 17:02:32 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_with_pipes(char **cmd, int i, t_env *env)
{
	char	**trunc_cmd;

	if (i > 0 && check_infiles(cmd) == 1)
	{
		trunc_cmd = ignore_infile(cmd);
		if (!trunc_cmd)
			return (-1);
		check_functions(trunc_cmd, env, 1);
		free_tab(trunc_cmd);
	}
	else if (i > 0 && check_infiles(cmd) == 2)
	{
		trunc_cmd = ignore_heredoc(cmd);
		if (!trunc_cmd)
			return (-1);
		check_functions(trunc_cmd, env, 1);
		free_tab(trunc_cmd);
	}
	else
		check_functions(cmd + 2, env, 1);
	if (dup2(1, STDIN_FILENO) == -1)
		return (-1);
	return (0);
}

int	create_heredoc(char **cmd, int i, int fd[2])
{
	char	*line;

	while (1)
	{
		line = NULL;
		ft_putstr_fd(">", 0);
		line = get_next_line(0);
		if (!line)
			return (ft_putstr_fd("bash: warning: here-document at line 15 delimited by \
end-of-file\n", 2), 0);
		if (!ft_strncmp(cmd[i + 1], line, ft_strlen(cmd[i + 1])))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
	return (0);
}
