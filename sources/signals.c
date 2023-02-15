/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:46:04 by lpupier           #+#    #+#             */
/*   Updated: 2023/02/15 15:24:51 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_ctrl_c(int id)
{
	(void)id;
	printf("[SIGNAL] CTRL+C\n");
	exit(1);
}

void	signal_ctrl_backslash(int id)
{
	(void)id;
	printf("[SIGNAL] CTRL+BACKSLASH\n");
	return ;
}
