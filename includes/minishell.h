/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 13:31:00 by lpupier           #+#    #+#             */
/*   Updated: 2023/01/20 14:05:38 by lpupier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Define
#ifndef MINISHELL_H
# define MINISHELL_H

// Librairies
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <stdlib.h>

// Headers
# include "../libft/libft.h"

// main.c

int		main(int argc, char **argv, char **envp);

// utils.c

char	*get_env(char **envp, char *request);
void	free_tab(char **tab);
int		get_array_size(char **envp);

// verify_args.c

char	**verify_args(char **new_cmd, char **envp);

// ft_echo.c

void	echo(char **cmd);

// ft_pwd.c

void	pwd(char **cmd, char **envp);

// ft_env.c

void	env(char **cmd, char **envp);

// ft_export.c

void	ft_export(char **cmd, char ***envp);

#endif