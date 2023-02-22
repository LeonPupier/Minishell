/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:10:19 by vcart             #+#    #+#             */
/*   Updated: 2023/02/22 08:48:16 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_known_cmd(char *cmd)
{
	if (!strcmp(cmd, "echo"))
		return (1);
	else if (!strcmp(cmd, "cd"))
		return (1);
	else if (!strcmp(cmd, "export"))
		return (1);
	else if (!strcmp(cmd, "unset"))
		return (1);
	else if (!strcmp(cmd, "pwd"))
		return (1);
	else if (!strcmp(cmd, "env"))
		return (1);
	else if (!strcmp(cmd, "exit"))
		return (1);
	else
		return (0);
}